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

void Player::setCloth(Entity* cloth) {
    this->Clothing = cloth;
}

Entity* Player::getCloth() const {
    return this->Clothing;
}


void Player::UpdateMovement(int steps){

    /////////////////////////////////////////////////////////
    //CODE TEMPORAIRE !!
    QPointF mousePos = mainScene->views().first()->mapToScene(mainScene->views().first()->mapFromGlobal(QCursor::pos()));
    // Récupérer la position de l'objet joueur
    QPointF playerPos = this->pos();

    // Calculer l'angle entre l'objet (joueur) et la souris
    qreal angle = std::atan2(mousePos.y() - playerPos.y(), mousePos.x() - playerPos.x()) * 180 / M_PI;

    // Appliquer la rotation à l'objet joueur
    qDebug() << "angle !" << angle;
    if(Clothing != nullptr)
        Clothing->setRotation(angle);  // Appliquer la rotation
    if(Weapon != nullptr)
        Weapon->setRotation(angle);  // Appliquer la rotation
    Entity::UpdateMovement(steps);
    /////////////////////////////////////////////////////////
 
}
