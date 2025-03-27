#include "Player.h"


Player::Player(int hit_points, Entity* Weapon, float speed, float attack_speed, QGraphicsItem* parent, QString filePath) : Entity(parent, filePath), hit_points(hit_points), Weapon(Weapon), speed(speed), attack_speed(attack_speed) {

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
void Player::setHitpoints(int hit_points) {
    this->hit_points = hit_points;
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
    return this->hit_points;
}