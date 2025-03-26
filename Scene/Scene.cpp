#include "Scene.h"
#include <QGraphicsRectItem>


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    qgti = new QGraphicsTextItem("CIR2 Nantes");
    this->addItem(qgti);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16); //toutes les 30 millisecondes
}


void Scene::update(){
    QPointF pos = qgti->pos(); //récupération de la position de l’objet qgti


    if (qgti->collidesWithItem(qgri)) {
        qDebug() << "Collision !";
       }
    else{
        qgti->setPos(pos.rx(), pos.ry()+5); //incrémentation de la coordonnée y
    }
       
}

Scene::~Scene() {

}
