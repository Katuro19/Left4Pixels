#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    QVector<Entity*> toPreLoad; //Add the firsts spawned items in this list so that the spawning is auto for those.


    Player* superCube = new Player(nullptr,
                QStringLiteral("../Resources/Characters/Player/player.png"),
                "player",
                nullptr,      // weapon
                1.0,          // attack_speed
                this);        // scene

    Entity* hands = new Entity(superCube,QStringLiteral("../Resources/Weapons/Katana.png"),"weapon", this);
    Entity* outfit = new Entity(superCube,QStringLiteral("../Resources/Cosmetics/sunglasses.png"),"cosmetic", this);
    Entity* zombie = new Entity(nullptr,QStringLiteral("../Resources/Characters/runner.png"),"runner", this);
    Projectile* projectile = new Projectile(nullptr,"../Resources/Items/image.png", "projectile", {100,100},{400,400},0,false,0,0,100,1, this);

    (*superCube).SetId(QStringLiteral("Cube"));
    //(*sword).SetId(QStringLiteral("Sword"));
    (*zombie).SetId(QStringLiteral("Zombie"));
    (*projectile).SetId(QStringLiteral("Projectile"));

    this->player = superCube;
    superCube->setWeapon(hands);
    superCube->setCloth(outfit);

    zombie->moveBy(-100,0);




    toPreLoad.push_back(player);
    toPreLoad.push_back(zombie);
    toPreLoad.push_back(hands);
    toPreLoad.push_back(outfit);
    toPreLoad.push_back(projectile);

    projectile->updateDirection();


    MapLoader* mapLoader = new MapLoader("Lotus", *this);

    for(Entity* entity : toPreLoad) {
        this->AddEntity(entity);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16); //60 FPS
}


Scene::~Scene() {
    qDebug() << "Destroying scene...";
    for (Entity* entity : Entities) {
        DeleteEntity(entity);
    }
    qDebug() << "Scene destroyed";
}

void Scene::update(){
    for(Entity* entity : Entities){ // Important note : only pushed entities (during the scene creation) are detected here.
        if (entity->GetEntityType() == "projectile"){
            //qDebug() << "Direction : x =" << entity->GetDirection().x() << ", y = " << entity->GetDirection().y();
            //qDebug() << "Position : x =" << entity->pos().x() << ", y = " << entity->pos().y();
        }
        if(entity->IsMoving()){ //if the entity move, maybe do something special idk...

        } 
        entity->UpdateMovement(); //Update the movement if needed

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

    qDebug() << "Spawning entity" << entity->GetId() << "of type" << entity->GetEntityType() <<"with UID" << this->totalEntitySpawned;
    entity->SetUid(this->totalEntitySpawned);
    this->addItem(entity);
    this->Entities.push_back(entity); //Add the new entity to the list, so that it will be called in the update loop !

    if(reposition)
        entity->setPos(spawnLocation);

    this->totalEntitySpawned++;
}


void Scene::DeleteEntity(Entity* entity){
    if (!entity) {
        qDebug() << "Entity is null!";
        return;
    }

    qDebug() << "Deleting entity" << entity->GetId() << "of type" << entity->GetEntityType() << "with UID" << entity->GetUid();

    int entityUid = entity->GetUid();
    this->removeItem(entity); //remove from scene !

    for (auto it = Entities.begin(); it != Entities.end(); ++it) {
        if ((*it)->GetUid() == entityUid) {
            Entities.erase(it); //Delete from the vector list, so thta we wont try to update it for exemple 
            break;
        }
    }
}


void Scene::SetPlayerPos(QPointF playerPos){
    this->player->setPos(playerPos);
}