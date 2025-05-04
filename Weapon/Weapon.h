#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "Scene.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>



//class Scene; //Forward declaration


class Weapon: public Entity {
private:
    int damage;
    QString weaponName;
    void UpdateMovement(float deltaTime, int steps) override;
    bool shoot = false;

    float RPS; //Round per sec - attack speed, in fact
    float baseRPS;
    int magazine=0;
    float speedBoost; //Speed boost is for the RPS, not the movement speed, duh.
    int bulletSpeed;
    float errorAngle;
    float reloadTime;


public:
    explicit Weapon(QGraphicsItem* parent = nullptr,QString filePath = "",QString entityType = "weapon",Scene* scene = nullptr,int damage = 10, QString name = "", bool verbose=false);
    ~Weapon();
    void setWeaponName(QString name);
    bool getIsShooting() const;
    void setIsShooting(bool shoot);
    QString getWeaponName() const;


    void LoadWeaponStats(QString name);


    void SetMagazine(int magSize);

    float GetRps();
    void SetRps(float newRps);
    
    float GetBaseRps();
    void SetBaseRps(float newRps);

    float GetSpeedBoost();
    void SetSpeedBoost(float boost);

    int GetDamage();
    void SetDamage(int newDamage);

    float GetErrorAngle();
    void SetErrorAngle(float newAngle);

    int GetBulletSpeed();
    void SetBulletSpeed(int newBulletSpeed);
    
    float GetReloadTime();
    void SetReloadTime(float newReloadTime);

};
#endif //WEAPON_H
