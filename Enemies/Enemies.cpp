#include "Enemies.h"


Enemy::Enemy(QGraphicsItem* parent, QString filePath, QString entityType, Scene* scene, bool verbose)
    : Entity(parent, filePath, entityType, scene, verbose){ //Call entity for the scene !

    this->SetZombieStats(entityType);



    
}

Enemy::~Enemy() {

}


void Enemy::UpdateMovement(float deltaTime, int steps){
    if(this->HP <= 0){
        this->TriggerDelete();
    }
    QPointF newDirection = parentScene->player->pos();
    //qDebug() << pos();
    //qDebug() << newDirection.x();
    this->SetDirection(newDirection.x(), newDirection.y());
    this->SetBaseSpeed(0);
    Entity::UpdateMovement(deltaTime, steps);

}


void Enemy::SetZombieStats(QString type){
    qDebug() << type;
    this->HP = 100;
}
