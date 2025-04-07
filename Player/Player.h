#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player: public Entity {
private:

    Entity* Weapon;

    int HP;
    float attack_speed;



public:

    explicit Player(QGraphicsItem* parent = nullptr, QString filePath = "", QString entityType = "player", Entity* weapon = nullptr, float attack_speed = 1.0);
   
    ~Player();

    void setWeapon(Entity* weapon);
    Entity* getWeapon() const;
    

    void setAttackSpeed(float attack_speed);
    float getAttackSpeed() const;

    
    void setHealthpoints(int HP);
    int getHealthpoints() const;


};


#endif //PLAYER_H
