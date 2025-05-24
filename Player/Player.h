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

        Weapon* weapons[3] = {nullptr, nullptr, nullptr}; // 3 weapons max
        unsigned int current_weapon = 0;
    
        QGraphicsTextItem* reloadingText;

    public:
        // Constructeur de Player
        explicit Player(QGraphicsItem* parent = nullptr,
                        QString filePath = "",
                        QString entityType = "player",
                        float attack_speed = 1.0,
                        Scene* scene = nullptr,
                        bool verbose = false); 
    
    ~Player();

    void SetWeapon(Weapon* weapon, unsigned int pos, QString name);
    Weapon* GetWeapon(unsigned int pos) const;
    Weapon* GetEquippedWeapon();


    void SetCloth(Entity* cloth);
    Entity* GetCloth() const;

    void SetAttackSpeed(float attack_speed);
    float GetAttackSpeed() const;

    unsigned int GetCurrentWeapon() const;
    void SetCurrentWeapon(unsigned int weapon);

    void SetHealthpoints(int HP);
    int GetHealthpoints() const;

    void UpdateMovement(float deltaTime, int steps = 1) override;

};


#endif //PLAYER_H
