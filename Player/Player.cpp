#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, float attack_speed, Scene* scene, bool verbose)
        : Entity(parent, filePath, entityType, scene, verbose), attack_speed(attack_speed){ //Call entity for the scene !

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


void Player::setWeapon(Weapon* weapon, unsigned int pos, QString name) {
    this->weapons[pos] = weapon;
    this->weapons[pos]->moveBy(100,0);
    this->weapons[pos]->LoadWeaponStats(name);
    //After moving the weapon, we need to reset its bound center
    QPointF parentCenter = this->boundingRect().center();
    QPointF localCenter = weapon->mapFromItem(weapon->parentItem(), parentCenter);
    weapon->setTransformOriginPoint(localCenter);
}

unsigned int Player::getCurrentWeapon() const {
    return current_weapon;
}
void Player::setCurrentWeapon(unsigned int weapon) {
    this->current_weapon = weapon;
}



Weapon* Player::getWeapon(unsigned int pos) const {
    return this->weapons[pos];
}

void Player::setCloth(Entity* cloth) {
    this->Clothing = cloth;
}

Entity* Player::getCloth() const {
    return this->Clothing;
}


void Player::UpdateMovement(float deltaTime, int steps) {
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
    QPointF playerPos = this->pos();

    // Get the angle between the player and the mouse
    qreal angle = std::atan2(mousePos.y() - playerPos.y(), mousePos.x() - playerPos.x()) * 180 / M_PI;

    // Apply rotation : We move the objects attached to the player, but not theplayer itself, to avoid wrong collisions !
    if(Clothing != nullptr)
        Clothing->setRotation(angle); 
    if(weapons[current_weapon]!= nullptr)
        weapons[current_weapon]->setRotation(angle);
        this->SetDefaultSpeedModifier(weapons[current_weapon]->GetSpeedBoost());

    Entity::UpdateMovement(deltaTime, steps);
 
}
