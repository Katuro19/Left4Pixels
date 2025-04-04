#include "Projectiles.h"


Projectile::Projectile(QGraphicsItem* parent,const QString filePath, const QString entityType, const QPointF target, const int damage, const bool isBreakable, const int pierces,const int bounces,const int HP,const float speed ) :
Entity(parent, filePath, entityType), damage(damage), isBreakable(isBreakable), pierces(pierces),bounces(bounces), HP(HP), target(target), speed(speed) {

}
Projectile::~Projectile() {

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