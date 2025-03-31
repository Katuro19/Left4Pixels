#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, Entity* Weapon, float attack_speed) : Entity(parent, filePath, entityType), HP(HP), Weapon(Weapon), attack_speed(attack_speed) {
    this->HP= 100;
}
Player::~Player() {

}
void Player::setWeapon(Entity* weapon) {
    this->Weapon = weapon;
}

void Player::setAttackSpeed(float attack_speed) {
    this->attack_speed = attack_speed;
}
void Player::setHitpoints(int HP) {
    this->HP = HP;
}
Entity* Player::getWeapon() {
    return this->Weapon;
}

float Player::getAttackSpeed() const {
    return this->attack_speed;
}
int Player::getHitpoints() const {
    return this->HP;
}