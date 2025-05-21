#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, 
        Weapon* weapon, float attack_speed, Scene* scene, bool verbose)
        : Entity(parent, filePath, entityType, scene, verbose), weapon(weapon), attack_speed(attack_speed){ //Call entity for the scene !

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


void Player::setWeapon(Weapon *weapon, QString name) {
    this->weapon = weapon;
    this->weapon->moveBy(100,0);
    this->weapon->LoadWeaponStats(name);
    //After moving the weapon, we need to reset its bound center
    QPointF parentCenter = this->boundingRect().center();
    QPointF localCenter = weapon->mapFromItem(weapon->parentItem(), parentCenter);
    weapon->setTransformOriginPoint(localCenter);

}





Weapon* Player::getWeapon() const {
    return this->weapon;
}

void Player::setCloth(Entity* cloth) {
    this->Clothing = cloth;
}

Entity* Player::getCloth() const {
    return this->Clothing;
}


void Player::UpdateMovement(float deltaTime, int steps){


    if(this->GetHp() <= 0){
        this->SetBaseSpeed(0);
        return;
    }

    for (auto it = this->graceTimers.begin(); it != this->graceTimers.end(); ) {
        it.value() -= deltaTime;

        if (it.value() <= 0) {
            it = graceTimers.erase(it); // efface l'entrée et avance le pointeur
        } else {
            ++it;
        }
    }

    // Get the mouse and player pos
    QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));

    QPointF centerInScene = this->GetRealCenter();
    
    // Get the angle between the player and the mouse
    qreal angle = std::atan2(mousePos.y() - centerInScene.y(), mousePos.x() - centerInScene.x()) * 180 / M_PI;

    //parentScene->addLine(playerPos.x(), playerPos.y(), mousePos.x(), mousePos.y(), QPen(Qt::red));


    // Apply rotation : We move the objects attached to the player, but not theplayer itself, to avoid wrong collisions !
    if(Clothing != nullptr)
        Clothing->setRotation(angle); 
    if(weapon != nullptr)
        weapon->setRotation(angle);
        this->SetDefaultSpeedModifier(weapon->GetSpeedBoost());

    Entity::UpdateMovement(deltaTime, steps);
 
}


