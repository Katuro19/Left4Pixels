#ifndef ENEMIES_H
#define ENEMIES_H

#include "Entity.h"
#include "Scene.h"

#include <string>  


class Scene; //Forward declaration


class Enemy : public Entity {
    private:

        void SetZombieStats(QString type); //Will set the visual of the zombies, and his stats

        Entity* Visual = nullptr; //This will be the visual : Like the player, the hitbox is not the whole zombie

        bool pDirectionDone = false;
    
    public:
        explicit Enemy(QGraphicsItem* parent = nullptr,
                        QString filePath = "",
                        QString entityType = "basic", //Possile entity type : basic, runner, spitter,
                        Scene* scene = nullptr,
                        bool verbose = false
                    ); 
    
        ~Enemy();

        void UpdateMovement(float deltaTime, int steps = 1) override;

        void ChooseDestination();


};


#endif //ENEMIES_H
