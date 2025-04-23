#ifndef WEAPON_H
#define WEAPON_H

#include "../Entity/Entity.h"

class Weapon: public Entity {
private:
    int damage;
    QString weaponName;


public:
    explicit Weapon(QGraphicsItem* parent = nullptr,QString filePath = "",QString entityType = "weapon",Scene* scene = nullptr,int damage = 10, QString name = "");
    ~Weapon();
    void setDamage(int damage);
    int getDamage() const;
    void setWeaponName(QString name);
    QString getWeaponName() const;
};
#endif //WEAPON_H
