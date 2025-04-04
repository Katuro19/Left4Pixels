#include "Weapon.h"

Weapon::Weapon(const int damage,const int id) : damage(damage), id(id){

}
Weapon::~Weapon() {

}
void Weapon::setDamage(const int damage) {
    this->damage = damage;
}
int Weapon::getDamage() const {
    return this->damage;
}

void Weapon::setId(const int id) {
    this->id = id;
}
int Weapon::getId() const {
    return this->id;
}
