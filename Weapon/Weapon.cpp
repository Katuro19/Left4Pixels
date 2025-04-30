#include "Weapon.h"

Weapon::Weapon(QGraphicsItem* parent,QString filePath,QString entityType,Scene* scene,const int damage, QString name) : Entity(parent, filePath, entityType, scene), damage(damage),weaponName(name){
    this->SetSpeedBoost(1.0);
}
Weapon::~Weapon() {

}
void Weapon::setDamage(const int damage) {
    this->damage = damage;
}
int Weapon::getDamage() const {
    return this->damage;
}

void Weapon::setWeaponName(const QString name) {
    this->weaponName = name;
}
QString Weapon::getWeaponName() const {
    return this->weaponName;
}

bool Weapon::getIsShooting() const {
    return this->shoot;
}

void Weapon::setIsShooting(const bool shoot) {
    this->shoot = shoot;
}

void Weapon::SetBaseRps(float newRps) {
    this->baseRPS = newRps;
    this->RPS = newRps;
}

void Weapon::SetRps(float newRps) {
    this->RPS = newRps;
}

void Weapon::SetSpeedBoost(float boost) {
    this->speedBoost = boost;
}

void Weapon::SetMagazine(int magSize){
    this->magazine = magSize;
}

float Weapon::GetRps() {
    return this->RPS;
}

float Weapon::GetBaseRps() {
    return this->baseRPS;
}

float Weapon::GetSpeedBoost() {
    return this->speedBoost;
}



void Weapon::UpdateMovement(float deltaTime, int steps) {

    float cooldownTimer = GetInternTimer() - (deltaTime * this->GetSpeedBoost());
    SetInternTimer(cooldownTimer);


    if (shoot) {
        if (!parentScene->views().isEmpty()) {



            //this->SetRps(this->GetBaseRps() * deltaTime); //Not really useful

            //qDebug() << "RPS : " << this->GetRps();

            if (GetInternTimer() <= 0.0f) {
                // Calculer la position du curseur de la souris
                QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));

                parentScene->handleShooting(mousePos);

                double cooldownSecs = 1.0f / this->GetBaseRps();


                SetInternTimer(cooldownSecs);

            }
        }
    }


    Entity::UpdateMovement(deltaTime, steps);  // Appel de la méthode de la classe de base pour le mouvement
}




