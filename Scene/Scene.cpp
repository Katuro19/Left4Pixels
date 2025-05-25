#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {


    bool manual_load = false;

    if (manual_load){

        QVector<Entity*> toPreLoad; //Add the firsts spawned items in this list so that the spawning is auto for those.


        Player* superCube = new Player(nullptr, //parent
                    QStringLiteral("../Resources/Textures/Characters/Player/player.png"), //image location
                    "player", //type
                    1.0,          // attack_speed
                    this,         // Scene (this)
                    true);        // verbose

        Weapon* primary = new Weapon(superCube,QStringLiteral("../Resources/Textures/Weapons/Hands/M249.png"),"weapon", this, 10, false);
        Weapon* secondary = new Weapon(superCube,QStringLiteral("../Resources/Textures/Weapons/Hands/deagle.png"),"weapon", this, 10, false);

        Entity* outfit = new Entity(superCube,QStringLiteral("../Resources/Textures/Cosmetics/Player/sunglasses.png"),"cosmetic", this);


        //Enemy* zombie = new Enemy(nullptr,QStringLiteral("../Resources/Textures/Characters/Zombies/runnerHitbox.png"),"runner", this, true);
        //Enemy* zombie2 = new Enemy(nullptr,QStringLiteral("../Resources/Textures/Characters/Zombies/basicHitbox.png"),"basic", this, true);

        // Projectile* projectile = new Projectile(nullptr,"../Resources/Items/image.png", "projectile", {100,100},{400,400},0,false,0,0,100,1, this);

        (*superCube).SetId(QStringLiteral("Cube"));
        //(*sword).SetId(QStringLiteral("Sword"));
        //(*zombie).SetId(QStringLiteral("Zombie"));
        (*outfit).SetId(QStringLiteral("sunglasses"));
        // (*projectile).SetId(QStringLiteral("Projectile"));

        this->player = superCube;superCube->SetWeapon(primary,0,"M249");
        superCube->SetWeapon(secondary,1,"deagle");


        superCube->SetCloth(outfit);


        //zombie->moveBy(3 * 256 , 3 * 256);
        //zombie2->moveBy(4 * 256 , 4 * 256);



        toPreLoad.push_back(player);
        //toPreLoad.push_back(zombie);
        //toPreLoad.push_back(zombie2);
        toPreLoad.push_back(primary);
        toPreLoad.push_back(secondary);

        toPreLoad.push_back(outfit);

        // toPreLoad.push_back(projectile);
        // projectile->updateDirection();


        srand(static_cast<unsigned int>(time(nullptr))); //Important for randomness


        MapLoader* mapLoader = new MapLoader("Debug", *this);

        for(Entity* entity : toPreLoad) {
            this->AddEntity(entity);
        }

        secondary->setVisible(false);
        //this->SpawnEnemies("basic", 2, QPointF(4 * 256, 4 * 256), QPointF(256, 0), true);


        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(16); //60 FPS

        frameTimer.start();
        menus = new Menus(this, parent);
    }

    else{

        srand(static_cast<unsigned int>(time(nullptr))); //Important for randomness


        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(16); //60 FPS

        frameTimer.start();
        menus = new Menus(this, parent);
    }

}


Scene::~Scene() {
    qDebug() << "☣️ Destroying scene...";

    for (int i = Entities.size() - 1; i >= 0; --i) {
        DeleteEntity(i);
    }

    qDebug() << "♻️ Scene destroyed";
}

void Scene::update() {

    if (isPaused){  //Permet de mettre en pause le jeu si on fait echap
        return;
    }

    qint64 elapsedMs = frameTimer.elapsed(); // temps depuis la dernière frame
    frameTimer.restart();                    // remet le chrono à 0
    float deltaTime = elapsedMs / 1000.0f;   // converti en secondes

    if(spawnTimer <= 0){
        WaveSpawn();
        spawnTimer = 3;
    } else {
        spawnTimer -= deltaTime;
    }

    DebugFps();

    for (int i = 0; i < Entities.size(); ++i) {
        Entity* entity = Entities[i];
        
        if (entity->WillDelete()) {
            DeleteEntity(i); // Delete entity using the index
            --i; // REmove one : This is to prevent crashes when checking the Entities list, since removing one item move everything to the left !!
        } else {
            // if (entity->IsMoving()) { //Used for animations! (one day)
              
            // }
            entity->UpdateMovement(deltaTime);
        }
    }

    CameraUpdate(player);
}

void Scene::CameraUpdate(Entity* entity) const {
    views().first()->centerOn(entity);

}


//This is only for the player
void Scene::keyPressEvent(QKeyEvent* event) {
    pressedKeys.insert(event->key());
    UpdateDirection();
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        togglePause();
        return;
    }
    else if(event->key() == Qt::Key_R){
        qDebug() << "here";
        this->player->GetWeapon(this->player->GetCurrentWeapon())->EmptyMagazine();
        return;
    }
    else if(event->key() == Qt::Key_A){
        qDebug() << "Current weapon : " << player->GetCurrentWeapon();

        if(this->player->GetCurrentWeapon() == 0 && this->player->GetWeapon(1) != nullptr){
            this->player->SetCurrentWeapon(1); //we equip the second weapon
            qDebug() << "Equipped second weapon";
            //this->SetScale(0.5);

        }
        else if(this->player->GetCurrentWeapon() == 1 && this->player->GetWeapon(0) != nullptr) {
            this->player->SetCurrentWeapon(0); //we equip the first weapon
            qDebug() << "Equipped first weapon";
            //this->SetScale(0.3);

        }
        return;
    }
    pressedKeys.remove(event->key());
    UpdateDirection();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Vérifier d'abord si nous sommes en pause - si oui, ne pas traiter les clics pour le joueur
    if (isPaused) {
        // Passer l'événement au gestionnaire par défaut pour que les CustomButtons puissent le recevoir
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    // Si nous ne sommes pas en pause, traiter normalement pour le joueur
    if (event->button() == Qt::LeftButton) {
        Weapon* weapon = this->player->GetWeapon(this->player->GetCurrentWeapon());
        if (weapon != nullptr) {
            if(weapon->GetRps() != 0) { //If the rps is 0, it's a melee weapon
                weapon->SetIsShooting(true);
            }
        }
    }

    else if (event->button() == Qt::RightButton) {
        qDebug() << "*insert a melee logic here*";
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // Vérifier d'abord si nous sommes en pause - si oui, ne pas traiter les clics pour le joueur
    if (isPaused) {
        // Passer l'événement au gestionnaire par défaut pour que les CustomButtons puissent le recevoir
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    // Si nous ne sommes pas en pause, traiter normalement pour le joueur
    if (event->button() == Qt::LeftButton) {
        Weapon* weapon = nullptr;
        if (this->player != nullptr) {
            weapon = this->player->GetWeapon(this->player->GetCurrentWeapon());
        } else {
            qDebug() << "Player is null, in mouseReleaseEvent()";
        }
        if (weapon != nullptr) {
            weapon->SetIsShooting(false);
        }
    }
}



void Scene::HandleShooting(const QPointF mousePos) {
    Weapon *weapon = this->player->GetEquippedWeapon();

    Projectile* projectile = GetProjectileFromPool();

    if (projectile) {
        projectile->Reset(
            mousePos,
            player->pos(),
            weapon->GetDamages(),
            weapon->GetBulletLife(),
            weapon->GetBulletSpeed(),
            weapon->GetErrorAngle()
        );
    } else {
        projectile = new Projectile(
            nullptr, //parent
            "../Resources/Textures/Projectiles/deagle_bullet.png",  //Path
            "projectile", //Type
            mousePos, //Target
            player->pos(), //start pos
            weapon->GetDamages(),  //Damage
            false, //Is breakable?
            0, //pierces
            0, //bounces
            weapon->GetBulletLife(), //HP
            weapon->GetBulletSpeed(), //Speed
            weapon->GetErrorAngle(), //Error angle
            this, //scene
            false //verbose
        );
        projectilePool.append(projectile); // Ajoute au pool pour la suite
        this->AddEntity(projectile);
    }
    
}


Projectile* Scene::GetProjectileFromPool() {
    for (Projectile* p : projectilePool) {
        if (!p->isVisible()) {
            return p;  // réutilise un projectile caché
        }
    }
    return nullptr; // pas dispo, faudra en créer un
}

void Scene::UpdateDirection() const {
    float dx = 0.0f;
    float dy = 0.0f;
    if (pressedKeys.contains(Qt::Key_Z))    dy -= 1.0f;
    if (pressedKeys.contains(Qt::Key_S))  dy += 1.0f;
    if (pressedKeys.contains(Qt::Key_Q))  dx -= 1.0f;
    if (pressedKeys.contains(Qt::Key_D)) dx += 1.0f;
    
    //Patch the navigation bug (being faster in diagonals)
    float magnitude = std::sqrt(dx*dx + dy*dy);
    if (magnitude > 0) {
        dx /= magnitude;
        dy /= magnitude;
    }




    this->player->SetDirection(dx,dy);
    this->player->SetMovement(!pressedKeys.isEmpty()); //This tells us if the player is moving

    //qDebug() << dx << dy;
    //qDebug() << this->player->IsMoving();

}


int Scene::GetScore(){
    return this->score;
}

void Scene::AddScore(int moreScore){
    this->score += moreScore;
}




void Scene::AddEntity(Entity* entity, bool reposition, QPointF spawnLocation){
    /*
        WARNING : AddEntity already push in the entities list ! no need to do it anywhere else !!
    
    */

    if(entity->IsVerbose())
        qDebug() << "⤵️ Spawning entity" << entity->GetId() << "of type" << entity->GetEntityType() <<"with UID" << this->totalEntitySpawned;

    entity->SetUid(this->totalEntitySpawned);
    this->addItem(entity);
    this->Entities.push_back(entity); //Add the new entity to the list, so that it will be called in the update loop !

    if(reposition)
        entity->setPos(spawnLocation);

    this->totalEntitySpawned++;
}


void Scene::DeleteEntity(int index) {
    if (index < 0 || index >= Entities.size()) return; //If index is invalid, we get out !

    Entity* entity = Entities[index]; //We grab our entity
    if (!entity) return; //If no entity, we get out 

    if (entity->IsVerbose())
        qDebug() << "🗑️ Deleting entity" << entity->GetId()
                 << "of type" << entity->GetEntityType()
                 << "with UID" << entity->GetUid();

    this->AddScore(entity->givenScore);
    this->removeItem(entity); // remove from QGraphicsScene
    Entities.erase(Entities.begin() + index); // Remove using the index directly taken from the main update
    delete entity;
}


void Scene::SpawnEnemies(QString type, int number, QPointF position, QPointF spacing, bool verbose){

    QString hitboxLink;

    if(type == "basic" || type == "spore" || type == "mother"){
        hitboxLink = "../Resources/Textures/Characters/Zombies/basicHitbox.png";

    } else if(type == "runner" || type == "pZombie" || type == "turret"){
        hitboxLink = "../Resources/Textures/Characters/Zombies/runnerHitbox.png";
    } else {
        QString errorMessage = "❌ Enemy type " + (type) + " does not exist or is not defined in Scene::SpawnEnemies";
        throw std::runtime_error(errorMessage.toStdString());
    }

    for(int i=0; i < number; i++){
        if(currentEnemyCount <= 35){
            this->currentEnemyCount++;
            Enemy* zombie = new Enemy(nullptr,hitboxLink,type, this, verbose);
            this->AddEntity(zombie, true, position);
            position += spacing;
        }
    }
    //Enemy* zombie2 = new Enemy(nullptr,QStringLiteral("../Resources/Textures/Characters/Zombies/basicHitbox.png"),"basic", this, true);

}


void Scene::WaveSpawn(){
    QPointF spawnPos; // Value is range

    for(int y=0; y < baseSpawnNumber; y++){
        spawnPos = GetSpawnPointAroundPlayer(1200);
        SpawnEnemies("basic",1, spawnPos, QPointF(0,0));
    }
    
    if(this->GetScore() >= miniBossSpawn){
        miniBossSpawn *= 2; //Double it and give it to the next person

        for(int i=0; i < baseSpawnNumber; i++){
            spawnPos = GetSpawnPointAroundPlayer(1200);
            int index = rand() % miniBossEnemies.size();  // entre 0 et size - 1
            qDebug() << index;
            QString chosenEnemy = miniBossEnemies[index];
            SpawnEnemies(chosenEnemy,1, spawnPos, QPointF(0,0), false);
        }

    }

    if(this->GetScore() >= bossSpawn){
        bossSpawn *= 2;
        for(int w=0; w < baseSpawnNumber; w++){
            spawnPos = GetSpawnPointAroundPlayer(1400); //spawn a bit further
            SpawnEnemies("mother",1, spawnPos, QPointF(0,0), true);
        }
        this->baseSpawnNumber++;

    }
}

QPointF Scene::GetSpawnPointAroundPlayer(float distance) {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI; // angle entre 0 et 2π
    float dx = std::cos(angle) * distance;
    float dy = std::sin(angle) * distance;

    QPointF playerPos = player->pos(); // ou player->GetRealCenter() si tu veux le centre exact
    return QPointF(playerPos.x() + dx, playerPos.y() + dy);
}



void Scene::SetPlayerPos(QPointF playerPos){
    this->player->setPos(playerPos);
}

void Scene::DebugFps(){
    static int frameCount = 0;
    static QElapsedTimer elapsedTimer;
    
    if (!elapsedTimer.isValid())
        elapsedTimer.start();
    
    frameCount++;
    
    if (elapsedTimer.elapsed() >= 1000) { // 1000 ms = 1s
        qDebug() << "FPS:" << frameCount;
        qDebug() << "Player HP :" << this->player->GetHp();
        qDebug() << "Score :" << this->GetScore();
        qDebug() << "Enemies !" << this->currentEnemyCount;

        frameCount = 0;
        elapsedTimer.restart();
    }
}


void Scene::togglePause() {

    isPaused = !isPaused;

    if (isPaused) {
        // Afficher le menu de pause
        menus->AfficherMenuPause(player->GetRealCenter(),
            [this]() {
                isPaused = false;
            },
            [this]() { SaveGame(this); },
            []() { qApp->quit(); }
        );
    }
    else {
        qDebug() << "Masquage du menu de pause";
        menus->MasquerMenuPause();
    }
}

void Scene::SetScale(float scale, int durationMs){
    QGraphicsView* view = this->views().first();
    view->resetTransform();         // Remet le zoom à 1.0
    view->scale(scale, scale);     // Applique le zoom voulu proprement
}

int Scene::GetSpawnedEntities() const{
    return this->totalEntitySpawned;
}
void Scene::SetSpawnedEntities(int newSpawnedEntities) {
    this->totalEntitySpawned = newSpawnedEntities;
}

bool Scene::GetIsPaused() const {
    return this->isPaused;
}
void Scene::SetIsPaused(bool paused) {
    this->isPaused = paused;
}

void Scene::SetMapName(QString name) {
    this->map_name = name;
}

QString Scene::GetMapName() {
    return this->map_name;
}

void Scene::SetMode(QString mode) {
    this->mode = mode;
}

QString Scene::GetMode() {
    return this->mode;
}

void Scene::SetPlayer(Player* player) {
    this->player = player;
}
Player* Scene::GetPlayer() const {
    return this->player;
}