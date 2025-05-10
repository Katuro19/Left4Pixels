#include "Weapon.h"

Weapon::Weapon(QGraphicsItem* parent,QString filePath,QString entityType,Scene* scene,const int damage, QString name, bool verbose) : Entity(parent, filePath, entityType, scene, verbose), damage(damage),weaponName(name){
    this->SetSpeedBoost(1.0);
}
Weapon::~Weapon() {

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

void Weapon::SetDamage(int newDamage){
    this->damage = newDamage;
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

int Weapon::GetDamage() {
    return this->damage;
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



void Weapon::UpdateMovement(float deltaTime, int steps) {

    float cooldownTimer = GetInternTimer() - (deltaTime * this->GetSpeedBoost());
    //qDebug() << cooldownTimer;
    SetInternTimer(cooldownTimer);


    if (shoot) {
        if (!parentScene->views().isEmpty()) {

            //this->SetRps(this->GetBaseRps() * deltaTime); //Not really useful

            //qDebug() << "RPS : " << this->GetRps();
            //qDebug() << GetInternTimer();

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




void Weapon::LoadWeaponStats(QString name) {
    //Prepare to load the weapon file
    QString fileName = "../Resources/Weapons/Stats/" + name + ".txt";
    QFile file(fileName);

    if (!file.exists()) {
        qWarning() << "Name is invalid:" << fileName;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error with file :" << fileName;
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
            SetDamage(values[0].toInt());
            SetBaseRps(values[1].toFloat());
            SetSpeedBoost(values[2].toFloat());
            SetMagazine(values[3].toInt());
            SetBulletSpeed(values[4].toInt());
            SetReloadTime(values[5].toFloat());
            SetErrorAngle(values[6].toFloat());
            SetBulletLife(values[7].toInt());



            if(this->IsVerbose()){
                qDebug() << "Damages:" << GetDamage();
                qDebug() << "RPS:" << GetRps();
                qDebug() << "Speed debuff :" << GetSpeedBoost();
                qDebug() << "Magazine size:" << this->magazine;
                qDebug() << "Bullet speed:" << GetBulletSpeed();
                qDebug() << "Reload Time:" << GetReloadTime();
                qDebug() << "Angle:" << GetErrorAngle();
                qDebug() << "Bullet HP:" << GetBulletLife();



            }

        } else {
            qWarning() << "Invalid line :"<< line;
        }
    }

    file.close();
}


