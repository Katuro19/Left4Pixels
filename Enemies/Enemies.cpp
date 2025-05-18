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

    if(this->Visual != nullptr)
        this->Visual->setRotation(angle);
    else
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
    Entity::UpdateMovement(deltaTime, steps);

}


void Enemy::SetZombieStats(QString type){


    int speed = 0;
    int hp = 1;
    Entity* outfit = nullptr;

    // note that the outfit type is still zombie !!
    if(type == "runner"){
        outfit = new Entity(this, QStringLiteral("../Resources/Textures/Characters/Zombies/runner.png"),"runner", this->parentScene);
        speed = 750;
        hp = 350;
    }
    else {
        qDebug() << "⚠️ Unknown enemy type :" << type;
        throw std::runtime_error("❌ Failed to load enemy. The given type of the entity referenced before is wrong\n❌ You can add the type in Enemies.cpp around line 70");
    }


    this->SetBaseSpeed(speed);
    this->SetHp(hp);
    this->Visual = outfit;
    
}
