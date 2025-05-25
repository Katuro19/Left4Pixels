#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "Scene.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>


//class Scene; //Forward declaration


class Weapon: public Entity {
private:
    void UpdateMovement(float deltaTime, int steps) override;
    bool shoot = false;

    float RPS; //Round per sec - attack speed, in fact
    float baseRPS;
    int magazine=0;
    float speedBoost; //Speed boost is for the RPS, not the movement speed, duh.
    int bulletSpeed;
    float errorAngle;
    float reloadTime;
    int bulletLife;
    QString name;

    float bulletPerShot = 0;

    bool isEquipped = false;


    QGraphicsTextItem* reloadingUi;

public:
    float reloadTimeout = 0;
    int maxMag=0;


    explicit Weapon(QGraphicsItem* parent = nullptr,QString filePath = "",QString entityType = "weapon",Scene* scene = nullptr,int damage = 10, bool verbose=false);
    ~Weapon();
    bool GetIsShooting() const;
    void SetIsShooting(bool shoot);


    void LoadWeaponStats(QString name);

    int GetMagazine() const;
    void SetMagazine(int magSize);
    void DecreaseMagazine();
    void EmptyMagazine();

    float GetRps();
    void SetRps(float newRps);
    
    float GetBaseRps();
    void SetBaseRps(float newRps);

    float GetSpeedBoost();
    void SetSpeedBoost(float boost);

    float GetErrorAngle();
    void SetErrorAngle(float newAngle);

    int GetBulletSpeed();
    void SetBulletSpeed(int newBulletSpeed);
    
    float GetReloadTime();
    void SetReloadTime(float newReloadTime);

    int GetBulletLife();
    void SetBulletLife(int newBulletLife);

    QString GetName();
    void SetName(QString name);

    void UnequipWeapon();
    void EquipWeapon();


};
#endif //WEAPON_H
