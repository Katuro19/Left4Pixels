#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Scene.h"

class Scene; //Forward declaration

class Player : public Entity {
    private:
        Entity* Clothing = nullptr;
        int HP;
        float attack_speed;

        Entity* Weapon = nullptr;
        QString weaponName;
    
    public:
        // Constructeur de Player
        explicit Player(QGraphicsItem* parent = nullptr,
                        QString filePath = "",
                        QString entityType = "player",
                        Entity* weapon = nullptr,
                        float attack_speed = 1.0,
                        Scene* scene = nullptr); 
    
    ~Player();

    void setWeapon(Entity* weapon, QString name);
    Entity* getWeapon() const;
  
    void setCloth(Entity* cloth);
    Entity* getCloth() const;

    void setAttackSpeed(float attack_speed);
    float getAttackSpeed() const;

    void setHealthpoints(int HP);
    int getHealthpoints() const;

    void UpdateMovement(int steps = 1) override;

};


#endif //PLAYER_H
