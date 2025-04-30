#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    QVector<Entity*> toPreLoad; //Add the firsts spawned items in this list so that the spawning is auto for those.


    Player* superCube = new Player(nullptr, //parent
                QStringLiteral("../Resources/Characters/Player/player.png"), //image location
                "player", //type
                nullptr,      // weapon
                1.0,          // attack_speed
                this,         // Scene (this)
                true);        // verbose

    Weapon* hands = new Weapon(superCube,QStringLiteral("../Resources/Weapons/deagle.png"),"weapon", this, 10, "deagle");
    Entity* outfit = new Entity(superCube,QStringLiteral("../Resources/Cosmetics/sunglasses.png"),"cosmetic", this);
    Entity* zombie = new Entity(nullptr,QStringLiteral("../Resources/Characters/runner.png"),"runner", this);
    // Projectile* projectile = new Projectile(nullptr,"../Resources/Items/image.png", "projectile", {100,100},{400,400},0,false,0,0,100,1, this);

    (*superCube).SetId(QStringLiteral("Cube"));
    //(*sword).SetId(QStringLiteral("Sword"));
    (*zombie).SetId(QStringLiteral("Zombie"));
    // (*projectile).SetId(QStringLiteral("Projectile"));

    this->player = superCube;
    superCube->setWeapon(hands,"deagle");
    superCube->setCloth(outfit);

    zombie->moveBy(-100,0);




    toPreLoad.push_back(player);
    toPreLoad.push_back(zombie);
    toPreLoad.push_back(hands);
    toPreLoad.push_back(outfit);

    // toPreLoad.push_back(projectile);
    // projectile->updateDirection();


    MapLoader* mapLoader = new MapLoader("Lotus", *this);

    for(Entity* entity : toPreLoad) {
        this->AddEntity(entity);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16); //60 FPS

    frameTimer.start();

}


Scene::~Scene() {
    qDebug() << "Destroying scene...";

    for (int i = Entities.size() - 1; i >= 0; --i) {
        DeleteEntity(i);
    }

    qDebug() << "Scene destroyed";
}

void Scene::update() {
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
    pressedKeys.remove(event->key());
    UpdateDirection();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Weapon* weapon = this->player->getWeapon();
        if (weapon != nullptr) {
            QString weapon_name = weapon->getWeaponName();

            if (weapon_name == "deagle"){
                weapon->setIsShooting(true);
            }

        }
    }
}

void Scene::handleShooting(const QPointF mousePos) {
    Projectile* projectile = new Projectile(nullptr, "../Resources/Items/image.png", "projectile", mousePos, player->pos(), 0, false, 0, 0, 100, player->getWeapon()->GetSpeed(), this);
    this->AddEntity(projectile);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton){
        Weapon* weapon = nullptr;
        if (this->player != nullptr){
            weapon = this->player->getWeapon();
            //qDebug() << "All is good";
        }else{
            qDebug() << "Player is null, in mouseReleaseEvent()";
        }
        if (weapon != nullptr){
            weapon->setIsShooting(false);
        }
    }
}


void Scene::UpdateDirection() const {
    float dx = 0.0f;
    float dy = 0.0f;
    if (pressedKeys.contains(Qt::Key_Up))    dy -= 1.0f;
    if (pressedKeys.contains(Qt::Key_Down))  dy += 1.0f;
    if (pressedKeys.contains(Qt::Key_Left))  dx -= 1.0f;
    if (pressedKeys.contains(Qt::Key_Right)) dx += 1.0f;
    
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




void Scene::AddEntity(Entity* entity, bool reposition, QPointF spawnLocation){
    /*
        WARNING : AddEntity already push in the entities list ! no need to do it anywhere else !!
    
    */

    if(entity->IsVerbose())
        qDebug() << "Spawning entity" << entity->GetId() << "of type" << entity->GetEntityType() <<"with UID" << this->totalEntitySpawned;

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
        qDebug() << "Deleting entity" << entity->GetId()
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