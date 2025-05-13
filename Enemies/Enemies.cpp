#include "Enemies.h"


Enemy::Enemy(QGraphicsItem* parent, QString filePath, QString entityType, Scene* scene, bool verbose, int baseHp)
        : Entity(parent, filePath, entityType, scene, verbose){ //Call entity for the scene !

    this->HP = 100;
}

Enemy::~Enemy() {

}