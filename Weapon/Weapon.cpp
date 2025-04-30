#include "Weapon.h"

Weapon::Weapon(QGraphicsItem* parent,QString filePath,QString entityType,Scene* scene,const int damage, QString name) : Entity(parent, filePath, entityType, scene), damage(damage),weaponName(name){

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

float Weapon::GetRps() {
    return this->RPS;
}

float Weapon::GetBaseRps() {
    return this->baseRPS;
}

void Weapon::UpdateMovement(float deltaTime, int steps) {
    if (shoot) {
        if (!parentScene->views().isEmpty()) {


            this->SetRps(this->GetBaseRps() * deltaTime);

            qDebug() << this->GetRps();

            // Calcul du temps entre chaque tir, basé uniquement sur l'attackSpeed du joueur
            float cooldownSecs = 1.0f / parentScene->player->getAttackSpeed();  // cooldown en secondes, sans deltaTime ici
            // qDebug() << "Attack Speed: " << parentScene->player->getAttackSpeed();
            // qDebug() << "Cooldown (secs): " << cooldownSecs;

            // Si le temps restant est inférieur ou égal à zéro, on peut tirer
            if (cooldownSecs <= 0.0f) {
                // Calculer la position du curseur de la souris
                QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));

                // Effectuer le tir
                parentScene->handleShooting(mousePos);

            }
        }
    }


    Entity::UpdateMovement(deltaTime, steps);  // Appel de la méthode de la classe de base pour le mouvement
}




void Weapon::SetMagazine(int magSize){
    this->magazine = magSize;
}