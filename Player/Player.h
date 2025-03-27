#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player: public Entity {
private:
    int hit_points;
    Entity* Weapon;
    float speed;
    float attack_speed;
public:
    explicit Player(int hit_points = 100, Entity* weapon = nullptr, float speed = 1.0, float attack_speed = 1.0, QGraphicsItem* parent = nullptr, QString filePath = "");
    ~Player();
    void setWeapon(Entity* weapon);
    void setSpeed(float speed);
    void setAttackSpeed(float attack_speed);
    void setHitpoints(int hit_points);
    Entity*  getWeapon();
    float getSpeed() const;
    float getAttackSpeed() const;
    int getHitpoints() const;


};


#endif //PLAYER_H
