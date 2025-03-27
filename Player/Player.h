#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player: public Entity {
private:

    Entity* Weapon;

    int HP;
    float speed;
    float attack_speed;


public:
    explicit Player(QGraphicsItem* parent = nullptr, QString filePath = "",Entity* weapon = nullptr, float speed = 1.0, float attack_speed = 1.0);
    ~Player();
    void setWeapon(Entity* weapon);
    void setSpeed(float speed);
    void setAttackSpeed(float attack_speed);
    void setHitpoints(int HP);
    Entity*  getWeapon();
    float getSpeed() const;
    float getAttackSpeed() const;
    int getHitpoints() const;


};


#endif //PLAYER_H
