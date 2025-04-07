#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, Entity* weapon,const float attack_speed) : Entity(parent, filePath, entityType), Weapon(weapon), attack_speed(attack_speed) {
    this->HP= 100;
}
Player::~Player() {

}


void Player::setAttackSpeed(const float attack_speed) {
    this->attack_speed = attack_speed;
}

float Player::getAttackSpeed() const {
    return this->attack_speed;
}


void Player::setHealthpoints(const int HP) {
    this->HP = HP;
}

int Player::getHealthpoints() const {
    return this->HP;
}


void Player::setWeapon(Entity* weapon) {
    this->Weapon = weapon;
}

Entity* Player::getWeapon() const {
    return this->Weapon;
}

