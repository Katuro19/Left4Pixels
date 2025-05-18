#include "Projectiles.h"
#include "Scene.h"

Projectile::Projectile(QGraphicsItem* parent, QString filePath, QString entityType,
    QPointF target, QPointF startPos, int damage, bool isBreakable,
    int pierces, int bounces, int HP, float speed, Scene* scene, bool verbose)
    : Entity(parent, filePath, entityType, scene, verbose),  isBreakable(isBreakable), pierces(pierces),bounces(bounces), target(target), startPos(startPos)  // Auto call of entity for the scene !
{
    this->setPos(startPos);
    this->updateDirection();
    this->SetBaseSpeed(speed);
    this->SetHp(HP);


    this->SetDamages(damage);
}


void Projectile::setBreakable(const bool isBreakable) {
    this->isBreakable = isBreakable;
}
void Projectile::setPierces(const int pierces) {
    this->pierces = pierces;
}
void Projectile::setBounces(const int bounces) {
    this->bounces = bounces;
}
void Projectile::setTarget(const QPointF target) {
    this->target = target;
}
bool Projectile::getBreakable() const {
    return this->isBreakable;
}
int Projectile::getPierces() const {
    return this->pierces;
}
int Projectile::getBounces() const {
    return this->bounces;
}

QPointF Projectile::getTarget() const {
    return this->target;
}

void Projectile::setStartingPos(QPointF pos) {
    this->startPos = pos;
}
QPointF Projectile::getStartingPos() const {
    return this->startPos;
}

void Projectile::updateDirection() {
    const qreal angle = std::atan2(this->target.y() - this->startPos.y(), this->target.x() - this->startPos.x());
    //this->setRotation(angle);
    QPointF direction = {qCos(angle),qSin(angle)};
    //qDebug() << "Direction : x =" << direction.x() << ", y = " << direction.y();
    this->SetDirection(direction.x(),direction.y());

}


void Projectile::UpdateMovement(float deltaTime, int steps){

    QRectF sceneBounds = this->parentScene->sceneRect(); // taille logique de la scène
    QRectF itemBounds = this->sceneBoundingRect();

    if (!sceneBounds.intersects(itemBounds)) {this->TriggerDelete();}


    float cooldownTimer = GetInternTimer() - deltaTime; //Only deltaTime because nothing affects the projectile
    SetInternTimer(cooldownTimer);

    if (GetInternTimer() <= 0.0f) {
        this->ReduceHp(); //We remove HP every second

        float cooldownSecs = 0.05f; //small cooldown before loosing HP again

        SetInternTimer(cooldownSecs);

    }

    //qDebug() << this->HP;
    if(this->HP <= 0){
        this->TriggerDelete();
        //parentScene->DeleteEntity(this);

    } else {
        //qDebug() << "Projectile pos =" << this->pos() << " target =" << this->target;
        this->ReduceHp(10);
        Entity::UpdateMovement(deltaTime, steps);
    }
}

