#include "Enemies.h"


Enemy::Enemy(QGraphicsItem* parent, QString filePath, QString entityType, Scene* scene, bool verbose)
    : Entity(parent, filePath, entityType, scene, verbose){ //Call entity for the scene !

    this->SetZombieStats(entityType);
    this->SetInternTimer(0);


    
}

Enemy::~Enemy() {

}


void Enemy::ChooseDestination(){

    QPointF playerPos = parentScene->player->pos();
    QPointF enemyPos = this->pos();

    QPointF direction = playerPos - enemyPos; //Diff between the positions, will help us calculate the directions

    setTransformOriginPoint(pixmap().width() / 2.0, pixmap().height() / 2.0);
    qreal angle = std::atan2(direction.y(), direction.x()) * 180.0 / M_PI;
    this->setRotation(angle);


    qreal length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    if (length != 0) {
        direction /= length;
    }

    this->SetDirection(direction.x(), direction.y());
}


void Enemy::UpdateMovement(float deltaTime, int steps){

    float grace = GetInternTimer();
    if(this->HP <= 0){
        this->TriggerDelete();
    }
    else if(grace > 0){
        grace -= deltaTime;
        if(grace < 0){
            grace = 0;
        }

        SetInternTimer(grace);
    }

    this->ChooseDestination();
    this->SetBaseSpeed(750.0); // vitesse au choix
    Entity::UpdateMovement(deltaTime, steps);

}


void Enemy::SetZombieStats(QString type){
    qDebug() << type;
    this->HP = 1000;
}
