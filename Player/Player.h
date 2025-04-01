#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player: public Entity {
private:

    Entity* Weapon;

    int HP;
    float attack_speed;



public:

    explicit Player(QGraphicsItem* parent = nullptr, QString filePath = "", QString entityType = "wall", Entity* weapon = nullptr, float attack_speed = 1.0);
   
    ~Player();

    void setWeapon(Entity* weapon);
    Entity* getWeapon();
    

    void setAttackSpeed(float attack_speed);
    float getAttackSpeed() const;

    
    void setHitpoints(int HP);
    int getHitpoints() const;


};


#endif //PLAYER_H
