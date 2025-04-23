#include "Weapon.h"

Weapon::Weapon(QGraphicsItem* parent,QString filePath,QString entityType,Scene* scene,const int damage, QString name) : Entity(parent, filePath, entityType, scene), damage(damage),weaponName(name){

}
Weapon::~Weapon() {

}
void Weapon::setDamage(const int damage) {
    this->damage = damage;
}
int Weapon::getDamage() const {
    return this->damage;
}

void Weapon::setWeaponName(const QString name) {
    this->weaponName = name;
}
QString Weapon::getWeaponName() const {
    return this->weaponName;
}
