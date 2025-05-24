#include "Weapon.h"

Weapon::Weapon(QGraphicsItem* parent,QString filePath,QString entityType,Scene* scene,const int damage, bool verbose) : Entity(parent, filePath, entityType, scene, verbose){
    this->SetSpeedBoost(1.0);
    this->SetInternTimer(1000);
    this->SetDamages(damage);

}
Weapon::~Weapon() {

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
    this->maxMag = magSize;
}

void Weapon::SetErrorAngle(float newAngle) {
    this->errorAngle = newAngle;
}

void Weapon::SetBulletSpeed(int newBulletSpeed) {
    this->bulletSpeed = newBulletSpeed;
}

void Weapon::SetReloadTime(float newReloadTime) {
    this->reloadTime = newReloadTime;
}

void Weapon::SetBulletLife(int newBulletLife){
    this->bulletLife = newBulletLife;
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

float Weapon::GetErrorAngle() {
    return this->errorAngle;
}

int Weapon::GetBulletSpeed() {
    return this->bulletSpeed;
}

float Weapon::GetReloadTime() {
    return this->reloadTime;
}

int Weapon::GetBulletLife(){
    return this->bulletLife;
}

QString Weapon::GetName() {
    return this->name;
}

void Weapon::SetName(QString name) {
    this->name = name;
}

int Weapon::GetMagazine() const {
    return this->magazine;
}

void Weapon::DecreaseMagazine(){
    this->magazine--;
}

void Weapon::EmptyMagazine(){
    this->magazine = 0;
}

void Weapon::UnequipWeapon(){
    //If we unequip while reloading, reset the reloading counter

    if(reloadTimeout > 0){
        reloadTimeout = this->GetReloadTime();
    }

    this->setIsShooting(false);
    isEquipped = false;
    this->setVisible(false);

}

void Weapon::EquipWeapon(){
    isEquipped = true;
    this->setVisible(true);

}


void Weapon::UpdateMovement(float deltaTime, int steps) {
    double cooldownSecs = 1.0f / this->GetBaseRps();
    float cooldownTimer = GetInternTimer() + (deltaTime);
    //qDebug() << "Timer actuel :" << cooldownTimer;
    SetInternTimer(cooldownTimer);

    if(reloadTimeout > 0 && isEquipped == true){
        reloadTimeout -= deltaTime;

        if(reloadTimeout <= 0)
            qDebug() << "Done!";
    }

    
    if(this->GetMagazine() <=0){
        reloadTimeout = this->GetReloadTime();
        this->SetMagazine(maxMag);
        qDebug() << "Reloading...";
    }

    if (shoot) {
        if (!parentScene->views().isEmpty()) {

            //qDebug() << "RPS : " << this->GetRps();

            if (GetInternTimer() >= cooldownSecs && reloadTimeout <= 0) {
                // Calculer la position du curseur de la souris
                
                QPointF mousePos = parentScene->views().first()->mapToScene(parentScene->views().first()->mapFromGlobal(QCursor::pos()));

                int shotToDo = 1;
                if(cooldownSecs < deltaTime){
                    bulletPerShot += deltaTime/cooldownSecs;
                    //qDebug() << "Delta time / cooldown :" << deltaTime << "/" << cooldownSecs;

                    shotToDo = int(bulletPerShot);
                    bulletPerShot -= shotToDo;
                    //qDebug() << "Shot to do :" << shotToDo;
                    //qDebug() << "Bullet per shot" << bulletPerShot;

                }

                //qDebug() << "Starting ...";
                for(int i=0; i < shotToDo; i++){
                    //qDebug() << "Shooting";
                    parentScene->handleShooting(mousePos);
                    this->DecreaseMagazine();
                    if(this->GetMagazine() <= 0){
                        break;
                    }
                }

                

                

                SetInternTimer(0);

            }
        }
    }


    Entity::UpdateMovement(deltaTime, steps);  // Appel de la méthode de la classe de base pour le mouvement
}




void Weapon::LoadWeaponStats(QString name) {
    //Prepare to load the weapon file
    QString fileName = "../Resources/WeaponsStats/Stats/" + name + ".txt";
    QFile file(fileName);

    if (!file.exists()) {
        qWarning() << "❌ Name is invalid:" << fileName;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ Error with file :" << fileName;
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();  // Remove spaces

        //If #, we dont read
        if (line.startsWith("#") || line.isEmpty()) {
            continue;
        }

        //We split
        QStringList values = line.split(";");

        if (values.size() == 8) {
            // We convert stats
            SetDamages(values[0].toInt());
            SetBaseRps(values[1].toFloat());
            SetSpeedBoost(values[2].toFloat());
            SetMagazine(values[3].toInt());
            SetBulletSpeed(values[4].toInt());
            SetReloadTime(values[5].toFloat());
            SetErrorAngle(values[6].toFloat());
            SetBulletLife(values[7].toInt());



            if(this->IsVerbose()){
                qDebug() << "Damages:" << GetDamages();
                qDebug() << "RPS:" << GetRps();
                qDebug() << "Speed debuff :" << GetSpeedBoost();
                qDebug() << "Magazine size:" << this->magazine;
                qDebug() << "Bullet speed:" << GetBulletSpeed();
                qDebug() << "Reload Time:" << GetReloadTime();
                qDebug() << "Angle:" << GetErrorAngle();
                qDebug() << "Bullet HP:" << GetBulletLife();



            }

        } else {
            qWarning() << "❌ Invalid line :"<< line;
        }
    }

    file.close();
}


