#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    /*
    qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    superCube = new QGraphicsRectItem(10, -500, 50, 50);
    //qgti = new QGraphicsTextItem("CIR2 Nantes", superCube); //Exemple pour ajouter un objet DANS le deuxieme cadre

    this->addItem(superCube);
    */



    Entity* superCube = new Entity(nullptr,QStringLiteral("randomPath"));
    Entity* sword = new Entity(superCube,QStringLiteral("../Resources/Textures/Objects/supersecretweapon.png"));
    Entity* zombie = new Entity(nullptr,QStringLiteral("../Resources/Characters/runner.png"));

    (*superCube).SetId(QStringLiteral("Cube"));
    (*sword).SetId(QStringLiteral("Sword"));
    (*zombie).SetId(QStringLiteral("Zombie"));
    //(*zombie).TriggerVisibility(false);



    this->Entities.push_back(superCube);
    sword->moveBy(-10, 0); // Déplace de +10 pixels en X (vers la droite)

    //this->Entities.push_back(sword);

    this->Entities.push_back(zombie);
    zombie->moveBy(-50,0);

    
    LoadEntities();


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16); 
}


Scene::~Scene() {
    for (Entity* entity : Entities) {
        delete entity; 
    }
}

void Scene::update(){
    
    QPointF pos = Entities[0]->pos(); //récupération de la position de l’objet qgti

     try{
        if (Entities[0]->collidesWithItem(Entities[1])) {
            qDebug() << "Collision !";
        }
    }
    catch (...){

    }
        
    
}

void Scene::keyPressEvent(QKeyEvent* event){
    QPointF pos = Entities[0]->pos();
    if (event->key() == Qt::Key_Up) {
        Entities[0]->setPos(pos.rx(), pos.ry()-5);
    } else if (event->key() == Qt::Key_Down) {
        Entities[0]->setPos(pos.rx(), pos.ry()+5);
    } else if (event->key() == Qt::Key_Left) {
        Entities[0]->setPos(pos.rx() - 5, pos.ry());
    } else if (event->key() == Qt::Key_Right) {
        Entities[0]->setPos(pos.rx() + 5, pos.ry());
    }
}




void Scene::LoadEntities(){
    int vectorSize = Entities.size();
    int counter = 1;
    for (Entity* entity : Entities) {
        qDebug() << qPrintable(QString("Loading entities (%1/%2)").arg(counter).arg(vectorSize));
        this->addItem(entity); 
        counter++;
    }
}
