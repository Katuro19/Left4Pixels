#include "Scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    /*
    qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    superCube = new QGraphicsRectItem(10, -500, 50, 50);
    //qgti = new QGraphicsTextItem("CIR2 Nantes", superCube); //Exemple pour ajouter un objet DANS le deuxieme cadre

    this->addItem(superCube);
    */


    Player* superCube = new Player(nullptr,QStringLiteral("randomPath"),"player");
    Entity* sword = new Entity(superCube,QStringLiteral("../Resources/Textures/Objects/supersecretweapon.png"),"weapon");
    Entity* zombie = new Entity(nullptr,QStringLiteral("../Resources/Characters/runner.png"),"runner");
    Entity* wall = new Entity(nullptr,QStringLiteral("../Resources/Textures/Tiles/THEwall.png"),"wall");

    
    (*superCube).SetId(QStringLiteral("Cube"));
    (*superCube).setWeapon(sword);
    (*sword).SetId(QStringLiteral("Sword"));
    (*zombie).SetId(QStringLiteral("Zombie"));
    (*wall).SetId(QStringLiteral("THEWall"));

    this->player = superCube;

    //(*zombie).TriggerVisibility(false);



    this->Entities.push_back(superCube);
    sword->moveBy(-10, 0); // move the sword

    //this->Entities.push_back(sword);
    this->Entities.push_back(zombie);
    zombie->moveBy(-100,0);


    this->Entities.push_back(wall);
    wall->moveBy(0,100);

    //zombie->SetDirection(1,0);

    
    LoadEntities();


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



void Scene::LoadEntities(){
    int vectorSize = Entities.size();
    int counter = 1;
    for (Entity* entity : Entities) {
        qDebug() << qPrintable(QString("Loading entities (%1/%2)").arg(counter).arg(vectorSize));
        entity->SetUid(counter - 1);
        this->addItem(entity);
        counter++;
    }
}
