#include "Weapon.h"

Weapon::Weapon(int damage, int id) : damage(damage), id(id){

}
Weapon::~Weapon() {

}

void Weapon::setDamage(int damage) {
    this->damage = damage;
}
int Weapon::getDamage() const {
    return this->damage;
}

void Weapon::setId(int id) {
    this->id = id;
}
int Weapon::getId() const {
    return this->id;
}
