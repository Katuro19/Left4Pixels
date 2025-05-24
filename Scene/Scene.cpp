#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    QVector<Entity*> toPreLoad; //Add the firsts spawned items in this list so that the spawning is auto for those.


    Player* superCube = new Player(nullptr, //parent
                QStringLiteral("../Resources/Textures/Characters/Player/player.png"), //image location
                "player", //type
                1.0,          // attack_speed
                this,         // Scene (this)
                true);        // verbose

    Weapon* primary = new Weapon(superCube,QStringLiteral("../Resources/Textures/Weapons/Hands/deagle.png"),"weapon", this, 10, false);
    Weapon* secondary = new Weapon(superCube,QStringLiteral("../Resources/Textures/Weapons/Hands/deagle.png"),"weapon", this, 10, false);

    Entity* outfit = new Entity(superCube,QStringLiteral("../Resources/Textures/Cosmetics/Player/sunglasses.png"),"cosmetic", this);
    //

    Enemy* zombie = new Enemy(nullptr,QStringLiteral("../Resources/Textures/Characters/Zombies/runnerHitbox.png"),"runner", this, true);
    Enemy* zombie2 = new Enemy(nullptr,QStringLiteral("../Resources/Textures/Characters/Zombies/basicHitbox.png"),"basic", this, true);

    // Projectile* projectile = new Projectile(nullptr,"../Resources/Items/image.png", "projectile", {100,100},{400,400},0,false,0,0,100,1, this);

    (*superCube).SetId(QStringLiteral("Cube"));
    //(*sword).SetId(QStringLiteral("Sword"));
    (*zombie).SetId(QStringLiteral("Zombie"));
    (*outfit).SetId(QStringLiteral("sunglasses"));
    // (*projectile).SetId(QStringLiteral("Projectile"));

    this->player = superCube;
    superCube->setWeapon(primary,0,"M1918");
    superCube->setWeapon(secondary,1,"deagle");

    superCube->setCloth(outfit);


    zombie->moveBy(3 * 256 , 3 * 256);
    zombie2->moveBy(4 * 256 , 4 * 256);



    toPreLoad.push_back(player);
    toPreLoad.push_back(zombie);
    toPreLoad.push_back(zombie2);
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


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16); //60 FPS

    frameTimer.start();
    menus = new Menus(this, parent);

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
        this->player->getWeapon(this->player->getCurrentWeapon())->EmptyMagazine();
        return;
    }
    else if(event->key() == Qt::Key_A){
        qDebug() << "Current weapon : " << player->getCurrentWeapon();

        if(this->player->getCurrentWeapon() == 0 && this->player->getWeapon(1) != nullptr){
            this->player->setCurrentWeapon(1); //we equip the second weapon
            qDebug() << "Equipped second weapon";
        }
        else if(this->player->getCurrentWeapon() == 1 && this->player->getWeapon(0) != nullptr) {
            this->player->setCurrentWeapon(0); //we equip the first weapon
            qDebug() << "Equipped first weapon";

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
        Weapon* weapon = this->player->getWeapon(this->player->getCurrentWeapon());
        if (weapon != nullptr) {
            if(weapon->GetRps() != 0) { //If the rps is 0, it's a melee weapon
                weapon->setIsShooting(true);
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
            weapon = this->player->getWeapon(this->player->getCurrentWeapon());
        } else {
            qDebug() << "Player is null, in mouseReleaseEvent()";
        }
        if (weapon != nullptr) {
            weapon->setIsShooting(false);
        }
    }
}



void Scene::handleShooting(const QPointF mousePos) {
    Weapon *weapon = this->player->getWeapon(this->player->getCurrentWeapon());

    Projectile* projectile = new Projectile(
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

    this->AddEntity(projectile);
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

    this->removeItem(entity); // remove from QGraphicsScene
    Entities.erase(Entities.begin() + index); // Remove using the index directly taken from the main update
    delete entity;
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
        frameCount = 0;
        elapsedTimer.restart();
    }
}


void Scene::togglePause() {

    isPaused = !isPaused;

    if (isPaused) {
        // Afficher le menu de pause
        menus->afficherMenuPause(player->pos(),
            [this]() {
                isPaused = false;
            },
            [this]() { SaveGame(this); },
            []() { qApp->quit(); }
        );
    }
    else {
        qDebug() << "Masquage du menu de pause";
        menus->masquerMenuPause();
    }
}

int Scene::getSpawnedEntities() {
    return this->totalEntitySpawned;
}

bool Scene::getIsPaused() {
    return this->isPaused;
}
void Scene::setMapName(QString name) {
    this->map_name = name;
}

QString Scene::getMapName() {
    return this->map_name;
}

void Scene::setMode(QString mode) {
    this->mode = mode;
}

QString Scene::getMode() {
    return this->mode;
}