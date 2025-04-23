#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, 
        Entity* weapon, float attack_speed, Scene* scene)
        : Entity(parent, filePath, entityType, scene), Weapon(weapon), attack_speed(attack_speed){ //Call entity for the scene !

    this->HP = 100;
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


void Player::setWeapon(Entity* weapon, QString name) {
    this->Weapon = weapon;
    this->Weapon->moveBy(10,0);
    this->weaponName = name;

    //After moving the weapon, we need to reset its bound center
    QPointF parentCenter = this->boundingRect().center();
    QPointF localCenter = weapon->mapFromItem(weapon->parentItem(), parentCenter);
    weapon->setTransformOriginPoint(localCenter);

}

Entity* Player::getWeapon() const {
    return this->Weapon;
}

void Player::setCloth(Entity* cloth) {
    this->Clothing = cloth;
}

Entity* Player::getCloth() const {
    return this->Clothing;
}


void Player::UpdateMovement(int steps){

    // Get the mouse and player pos
    QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));
    QPointF playerPos = this->pos();

    // Get the angle between the player and the mouse
    qreal angle = std::atan2(mousePos.y() - playerPos.y(), mousePos.x() - playerPos.x()) * 180 / M_PI;

    // Apply rotation : We move the objects attached to the player, but not theplayer itself, to avoid wrong collisions !
    if(Clothing != nullptr)
        Clothing->setRotation(angle); 
    if(Weapon != nullptr)
        Weapon->setRotation(angle); 


    Entity::UpdateMovement(steps);
 
}
