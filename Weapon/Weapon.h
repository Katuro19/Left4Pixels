#ifndef WEAPON_H
#define WEAPON_H

#include "../Entity/Entity.h"

class Weapon: public Entity {
private:
    int damage;
    int id;

public:
    explicit Weapon(int damage, int id);
    ~Weapon();
    void setDamage(int damage);
    void setId(int id);
    int getDamage() const;
    int getId() const;
};
#endif //WEAPON_H
