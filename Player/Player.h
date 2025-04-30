#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Weapon.h"
#include "Scene.h"


class Scene; //Forward declaration
class Weapon; //Forward declaration

class Player : public Entity {
    private:
        Entity* Clothing = nullptr;
        float attack_speed;

        Weapon* weapon = nullptr;
    
    public:
        // Constructeur de Player
        explicit Player(QGraphicsItem* parent = nullptr,
                        QString filePath = "",
                        QString entityType = "player",
                        Weapon* weapon = nullptr,
                        float attack_speed = 1.0,
                        Scene* scene = nullptr,
                        bool verbose = false); 
    
    ~Player();

    void setWeapon(Weapon* weapon, QString name);
    Weapon* getWeapon() const;
  
    void setCloth(Entity* cloth);
    Entity* getCloth() const;

    void setAttackSpeed(float attack_speed);
    float getAttackSpeed() const;
    void SetSpeedByName(Weapon *weapon, QString weaponName);

    void setHealthpoints(int HP);
    int getHealthpoints() const;

    void UpdateMovement(float deltaTime, int steps = 1) override;


};


#endif //PLAYER_H
