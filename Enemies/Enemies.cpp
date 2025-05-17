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
    Entity::UpdateMovement(deltaTime, steps);

}


void Enemy::SetZombieStats(QString type){
    qDebug() << type;
}
