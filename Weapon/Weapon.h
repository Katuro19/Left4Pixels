#ifndef WEAPON_H
#define WEAPON_H
#include "Entity.h"
#include "Scene.h"

//class Scene; //Forward declaration


class Weapon: public Entity {
private:
    int damage;
    QString weaponName;
    void UpdateMovement(float deltaTime, int steps) override;
    bool shoot = false;
    QElapsedTimer fireRateTimer;
    float fireCooldown = 300.0f; // cooldown en millisecondes (300ms entre deux tirs)


public:
    explicit Weapon(QGraphicsItem* parent = nullptr,QString filePath = "",QString entityType = "weapon",Scene* scene = nullptr,int damage = 10, QString name = "");
    ~Weapon();
    void setDamage(int damage);
    int getDamage() const;
    void setWeaponName(QString name);
    bool getIsShooting() const;
    void setIsShooting(bool shoot);
    QString getWeaponName() const;
};
#endif //WEAPON_H
