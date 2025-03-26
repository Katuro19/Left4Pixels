#include "Scene.h"
#include <QGraphicsRectItem>


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    container = new QGraphicsRectItem(10, -500, 50, 50);
    //qgti = new QGraphicsTextItem("CIR2 Nantes", container); //Exemple pour ajouter un objet DANS le deuxieme cadre

    this->addItem(container);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30); //toutes les 30 millisecondes
}


void Scene::update(){
    QPointF pos = container->pos(); //récupération de la position de l’objet qgti


    if (container->collidesWithItem(qgri)) {
        qDebug() << "Collision !";
       }
    else{
        container->setPos(pos.rx(), pos.ry()+5); //incrémentation de la coordonnée y
    }
       
}

Scene::~Scene() {

}
