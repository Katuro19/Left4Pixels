#include "Player.h"


Player::Player(QGraphicsItem* parent, QString filePath, QString entityType, float attack_speed, Scene* scene, bool verbose)
        : Entity(parent, filePath, entityType, scene, verbose), attack_speed(attack_speed){ //Call entity for the scene !

    this->HP = 100;


    QGraphicsTextItem* textItem = new QGraphicsTextItem("Reload: 3.5s");
    textItem->setDefaultTextColor(Qt::red);     // couleur du texte
    textItem->setFont(QFont("Arial", 24, QFont::Bold)); // police, taille, style
    textItem->setZValue(1000);
    parentScene->addItem(textItem);
    textItem->setParentItem(this);

    qreal offsetY = 256;
    textItem->setPos(0,offsetY);

    reloadingText = textItem;


    QGraphicsTextItem* ammoText = new QGraphicsTextItem("0 / 0");
    ammoText->setFont(QFont("Arial", 45, QFont::Bold));
    ammoText->setDefaultTextColor(Qt::white);
    ammoText->setPos(this->GetRealCenter() + QPointF(-256 * 4 + 100, 256 * 3.4)); // Décalé de l’icône
    parentScene->addItem(ammoText);
    ammoText->setParentItem(this);


    this->ammoUi = ammoText;
    ammoUi->setZValue(1000);

    QGraphicsTextItem* scoreText = new QGraphicsTextItem("Score : 0");
    scoreText->setFont(QFont("Arial", 45, QFont::Bold));
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setPos(this->GetRealCenter() + QPointF(-256 * 3.7, - 256 * 3.7)); // Décalé de l’icône
    parentScene->addItem(scoreText);
    scoreText->setParentItem(this);


    this->scoreUi = scoreText;
    scoreUi->setZValue(1000);


}

Player::~Player() {

}


void Player::SetAttackSpeed(const float attack_speed) {
    this->attack_speed = attack_speed;
}

float Player::GetAttackSpeed() const {
    return this->attack_speed;
}


void Player::SetHealthpoints(const int HP) {
    this->HP = HP;
}

int Player::GetHealthpoints() const {
    return this->HP;
}


void Player::SetWeapon(Weapon* weapon, unsigned int pos, QString name) {
    if (weapon == nullptr){
        this->weapons[pos] = nullptr;
        qWarning() << "A weapon was set to null with pos: " << pos;
        return;
    }

    this->weapons[pos] = weapon;
    this->weapons[pos]->moveBy(100,0);
    this->weapons[pos]->LoadWeaponStats(name);
    this->weapons[pos]->SetName(name);

    if(pos != 0){
        weapon->UnequipWeapon();
    }

    weapon->EquipWeapon();
    //After moving the weapon, we need to reset its bound center
    QPointF parentCenter = this->boundingRect().center();
    QPointF localCenter = weapon->mapFromItem(weapon->parentItem(), parentCenter);
    weapon->setTransformOriginPoint(localCenter);
}

unsigned int Player::GetCurrentWeapon() const {
    return current_weapon;
}
void Player::SetCurrentWeapon(unsigned int weapon) {
    //qDebug() << "Equipping " << weapon;
    Weapon* equippedWeapon = GetEquippedWeapon();
    equippedWeapon->UnequipWeapon();

    this->current_weapon = weapon;
    this->GetEquippedWeapon()->EquipWeapon();
}



Weapon* Player::GetWeapon(unsigned int pos) const {
    return this->weapons[pos];
}

Weapon* Player::GetEquippedWeapon(){
    return this->weapons[current_weapon];
}

void Player::SetCloth(Entity* cloth) {
    this->Clothing = cloth;
}

Entity* Player::GetCloth() const {
    return this->Clothing;
}


void Player::UpdateMovement(float deltaTime, int steps) {

    int currentAmmo = this->GetEquippedWeapon()->GetMagazine();
    int maxAmmo = this->GetEquippedWeapon()->maxMag;
    this->ammoUi->setPlainText(QString("%1 / %2").arg(currentAmmo).arg(maxAmmo));
    this->ammoUi->setZValue(1000);


    if(this->GetHp() <= 0){
        this->SetBaseSpeed(0);
        //qDebug() << "you are die";
        if (parentScene->GetIsDead()) {
            qDebug() << "Scene is already dead, skipping player update.";
            return; // If the scene is already dead, we skip the update
        }
        else{
            parentScene->SetIsDead(true); // Set the scene to dead state
        }
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


    float weaponReloadTimeout = (this->GetEquippedWeapon())->reloadTimeout;

    if(weaponReloadTimeout > 0){
        //reloadingText->setPos(this->mapToScene(0, 0)); // place à la même position que l'item
        reloadingText->setPlainText(QString("Reloading %1s").arg(QString::number(weaponReloadTimeout, 'f', 1)));
        reloadingText->setVisible(true);
        this->ammoUi->setPlainText(QString("%1 / %2").arg(0).arg(maxAmmo));


    } else {reloadingText->setVisible(false);}

    // Get the mouse and player pos
    QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));

    QPointF centerInScene = this->GetRealCenter();
    
    // Get the angle between the player and the mouse
    qreal angle = std::atan2(mousePos.y() - centerInScene.y(), mousePos.x() - centerInScene.x()) * 180 / M_PI;

    //parentScene->addLine(playerPos.x(), playerPos.y(), mousePos.x(), mousePos.y(), QPen(Qt::red));


    // Apply rotation : We move the objects attached to the player, but not theplayer itself, to avoid wrong collisions !
    if(Clothing != nullptr)
        Clothing->setRotation(angle); 
    if(weapons[current_weapon]!= nullptr)
        weapons[current_weapon]->setRotation(angle);
        this->SetDefaultSpeedModifier(weapons[current_weapon]->GetSpeedBoost());

    Entity::UpdateMovement(deltaTime, steps);
 
}


