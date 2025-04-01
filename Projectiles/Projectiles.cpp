#include "Projectiles.h"


Projectile::Projectile(QGraphicsItem* parent, QString filePath, QString entityType, int damage, bool isBreakble, int peirces, int bounces, int HP) : Entity(parent, filePath, entityType), damage(damage), isBreakble(isBreakble), peirces(peirces),bounces(bounces), HP(HP) {

}
Projectile::~Projectile() {

}
void Projectile::setDamage(int damage) {
    this->damage = damage;
}
void Projectile::setBreakble(bool isBreakble) {
    this->isBreakble = isBreakble;
}
void Projectile::setPeirces(int peirces) {
    this->peirces = peirces;
}
void Projectile::setBounces(int bounces) {
    this->bounces = bounces;
}
void Projectile::setHP(int HP) {
    this->HP = HP;
}
int Projectile::getDamage() const {
    return this->damage;
}
bool Projectile::getBreakble() const {
    return this->isBreakble;
}
int Projectile::getPeirces() const {
    return this->peirces;
}
int Projectile::getBounces() const {
    return this->bounces;
}
int Projectile::getHP() const {
    return this->HP;
}