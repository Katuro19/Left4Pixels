#include "Projectiles.h"



Projectile::Projectile(QGraphicsItem* parent,const QString filePath, const QString entityType, const QPointF target, QPointF startPos,const int damage, const bool isBreakable, const int pierces,const int bounces,const int HP,const float speed ) :
Entity(parent, filePath, entityType), damage(damage), isBreakable(isBreakable), pierces(pierces),bounces(bounces), HP(HP), target(target), startPos(startPos),speed(speed) {
    if (parent != nullptr) {
        this->setStartingPos(parent->pos());
    }
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
    const qreal angle = std::atan2(this->target.y() - this->pos().y(), this->target.x() - this->pos().x());
    QPointF direction = {qCos(angle),qSin(angle)};
    qDebug() << "Direction : x =" << direction.x() << ", y = " << direction.y();
    this->SetDirection(direction.x(),direction.y());
}

void Projectile::UpdateMovement(int steps){
    this->HP--;
    if(this->HP <= 0){
        mainScene->DeleteEntity(this);
        qDebug() << "Finishing projectile update movment delete";
        return;
    }
    Entity::UpdateMovement(steps);
}
