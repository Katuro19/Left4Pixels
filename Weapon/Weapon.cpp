#include "Weapon.h"

Weapon::Weapon(QGraphicsItem* parent,QString filePath,QString entityType,Scene* scene,const int damage, QString name) : Entity(parent, filePath, entityType, scene), damage(damage),weaponName(name){
    fireRateTimer.start(); // démarre le chrono
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

bool Weapon::getIsShooting() const {
    return this->shoot;
}

void Weapon::setIsShooting(const bool shoot) {
    this->shoot = shoot;
}

void Weapon::UpdateMovement(float deltaTime, int steps) {
    if (shoot){ 
        if (!parentScene->views().isEmpty()) {
            float cooldownMs = 1000.0f / parentScene->player->getAttackSpeed();
            if (fireRateTimer.elapsed() >= cooldownMs) {
                QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));
                parentScene->handleShooting(mousePos);
                fireRateTimer.restart(); // reset le timer après chaque tir
            }
        }
    }
    Entity::UpdateMovement(deltaTime, steps); // Call the base class method to handle movement

}



void Weapon::SetMagazine(int magSize){
    this->magazine = magSize;
}