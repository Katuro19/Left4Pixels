#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, Entity* weapon,const float attack_speed) : Entity(parent, filePath, entityType), Weapon(weapon), attack_speed(attack_speed) {
    this->HP= 100;
}
Player::~Player() {

}
void Player::setWeapon(Entity* weapon) {
    this->Weapon = weapon;
}

void Player::setAttackSpeed(const float attack_speed) {
    this->attack_speed = attack_speed;
}
void Player::setHitpoints(const int HP) {
    this->HP = HP;
}
Entity* Player::getWeapon() const {
    return this->Weapon;
}

float Player::getAttackSpeed() const {
    return this->attack_speed;
}
int Player::getHitpoints() const {
    return this->HP;
}