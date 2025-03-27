#include "Player.h"


Player::Player(int HP, Entity* Weapon, float speed, float attack_speed, QGraphicsItem* parent, QString filePath) : Entity(parent, filePath), HP(HP), Weapon(Weapon), speed(speed), attack_speed(attack_speed) {

}
Player::~Player() {

}
void Player::setWeapon(Entity* weapon) {
    this->Weapon = weapon;
}
void Player::setSpeed(float speed) {
    this->speed = speed;
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
float Player::getSpeed() const {
    return this->speed;
}
float Player::getAttackSpeed() const {
    return this->attack_speed;
}
int Player::getHitpoints() const {
    return this->HP;
}