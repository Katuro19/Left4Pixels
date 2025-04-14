#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    QVector<Entity*> toPreLoad; //Add the firsts spawned items in this list so that the spawning is auto for those.


    Player* superCube = new Player(nullptr,QStringLiteral("../Resources/Characters/Player/player.png"),"player");
    Entity* hands = new Entity(superCube,QStringLiteral("../Resources/Weapons/Katana.png"),"weapon");
    Entity* outfit = new Entity(superCube,QStringLiteral("../Resources/Cosmetics/sunglasses.png"),"cosmetic");
    Entity* zombie = new Entity(nullptr,QStringLiteral("../Resources/Characters/runner.png"),"runner");
    Projectile* projectile = new Projectile(nullptr,"../Resources/Items/image.png", "projectile", {100,100},{400,400},0,false,0,0,100,1);

    (*superCube).SetId(QStringLiteral("Cube"));
    //(*sword).SetId(QStringLiteral("Sword"));
    (*zombie).SetId(QStringLiteral("Zombie"));
    (*projectile).SetId(QStringLiteral("Projectile"));

    this->player = superCube;

    //superCube->setWeapon(sword);
    superCube->setWeapon(hands);
    superCube->setCloth(outfit);
    superCube->SetScene(*this);

    //(*zombie).TriggerVisibility(false);
    //zombie->SetDirection(1,0);
    //sword->moveBy(-10, 0); // move the sword
    zombie->moveBy(-100,0);




    //player->setTransformOriginPoint(13,13);

    toPreLoad.push_back(player);
    toPreLoad.push_back(zombie);
    toPreLoad.push_back(hands);
    toPreLoad.push_back(outfit);
    toPreLoad.push_back(projectile);
    //toPreLoad.push_back(sword);
    //AddEntity(projectile,true,projectile->getStartingPos());
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
    for (Entity* entity : Entities) {
        delete entity; 
    }
}

void Scene::update(){
    for(Entity* entity : Entities){ // Important note : only pushed entities (during the scene creation) are detected here.
        if (entity->GetEntityType() == "projectile"){
            qDebug() << "Position : x =" << entity->pos().x() << ", y = " << entity->pos().y();
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

    qDebug() << dx << dy;
    qDebug() << this->player->IsMoving();

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
    qDebug() << "Deleting entity" << entity->GetId() << "of type" << entity->GetEntityType() <<"with UID" << entity->GetUid();
    this->removeItem(entity); //Remove from scene
    qDebug() << "oui";
    // Trouver et supprimer
    auto it = std::find(Entities.begin(), Entities.end(), entity);
    if (it != Entities.end()) {
        delete *it;               // Libère la mémoire
        Entities.erase(it);       // Enlève du vector
    }

}


void Scene::SetPlayerPos(QPointF playerPos){
    this->player->setPos(playerPos);
}