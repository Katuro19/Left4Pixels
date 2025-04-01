#include "Projectiles.h"


Projectile::Projectile(QGraphicsItem* parent, QString filePath, QString entityType, int damage, bool isBreakble, int peirces, int bounces, int HP, QPointF target) : Entity(parent, filePath, entityType), damage(damage), isBreakble(isBreakble), peirces(peirces),bounces(bounces), HP(HP), target(target) {

}
Projectile::~Projectile() {

}
void Projectile::setDamage(int damage) {
    this->damage = damage;
}
void Projectile::setBreakble(bool isBreakble) {
    this->isBreakble = isBreakble;
}
void Projectile::setPierces(int peirces) {
    this->peirces = peirces;
}
void Projectile::setBounces(int bounces) {
    this->bounces = bounces;
}
void Projectile::setHP(int HP) {
    this->HP = HP;
}
void Projectile::setTarget(QPointF target) {
    this->target = target;
}
int Projectile::getDamage() const {
    return this->damage;
}
bool Projectile::getBreakble() const {
    return this->isBreakble;
}
int Projectile::getPierces() const {
    return this->peirces;
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