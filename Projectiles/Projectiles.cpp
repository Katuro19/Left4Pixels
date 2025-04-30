#include "Projectiles.h"
#include "Scene.h"

Projectile::Projectile(QGraphicsItem* parent, QString filePath, QString entityType,
    QPointF target, QPointF startPos, int damage, bool isBreakable,
    int pierces, int bounces, int HP, float speed, Scene* scene, bool verbose)
    : Entity(parent, filePath, entityType, scene, verbose),  isBreakable(isBreakable), pierces(pierces),bounces(bounces), HP(HP), target(target), startPos(startPos),speed(speed)  // Auto call of entity for the scene !
{
    this->setPos(startPos);
    this->updateDirection();
}

void Projectile::setDamage(const int damage) {
    this->damage = damage;
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
void Projectile::setHP(const int HP) {
    this->HP = HP;
}
void Projectile::setTarget(const QPointF target) {
    this->target = target;
}
int Projectile::getDamage() const {
    return this->damage;
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
int Projectile::getHP() const {
    return this->HP;
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
    this->setRotation(angle);
    QPointF direction = {qCos(angle),qSin(angle)};
    //qDebug() << "Direction : x =" << direction.x() << ", y = " << direction.y();
    this->SetDirection(direction.x(),direction.y());

}


void Projectile::UpdateMovement(float deltaTime, int steps){
    this->HP--;
    //qDebug() << this->HP;
    if(this->HP <= 0){
        this->TriggerDelete();
        //parentScene->DeleteEntity(this);

    } else {
        //qDebug() << "Projectile pos =" << this->pos() << " target =" << this->target;
        Entity::UpdateMovement(deltaTime, steps);
    }
}

