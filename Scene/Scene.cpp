#include "Scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    /*
    qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    superCube = new QGraphicsRectItem(10, -500, 50, 50);
    //qgti = new QGraphicsTextItem("CIR2 Nantes", superCube); //Exemple pour ajouter un objet DANS le deuxieme cadre

    this->addItem(superCube);
    */

    QString ip = "...";

    Entity* superCube = new Entity(nullptr,ip);
    Entity* qgri = new Entity;

    this->Entities.push_back(superCube);
    this->Entities.push_back(qgri);

    
    LoadEntities();


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30); //toutes les 30 millisecondes
}


Scene::~Scene() {
    for (Entity* entity : Entities) {
        delete entity; 
    }
}

void Scene::update(){
    QPointF pos = Entities[0]->pos(); //récupération de la position de l’objet qgti

    if (Entities[0]->collidesWithItem(Entities[1])) {
        qDebug() << "Collision !";
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
    for (Entity* entity : Entities) {
        this->addItem(entity); 
    }
}
