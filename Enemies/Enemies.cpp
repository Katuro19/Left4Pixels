#include "Enemies.h"


Enemy::Enemy(QGraphicsItem* parent, QString filePath, QString entityType, Scene* scene, bool verbose, int baseHp)
        : Entity(parent, filePath, entityType, scene, verbose){ //Call entity for the scene !

    this->HP = baseHp;
}

Enemy::~Enemy() {

}


void Enemy::UpdateMovement(float deltaTime, int steps){
    if(this->HP <= 0){
        this->TriggerDelete();
    }
    Entity::UpdateMovement(deltaTime, steps);

}