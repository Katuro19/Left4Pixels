#ifndef ENEMIES_H
#define ENEMIES_H

#include "Entity.h"
#include "Scene.h"


class Scene; //Forward declaration


class Enemy : public Entity {
    private:

        void SetZombieStats(QString type);

    
    public:
        explicit Enemy(QGraphicsItem* parent = nullptr,
                        QString filePath = "",
                        QString entityType = "basic", //Possile entity type : basic, runner, spitter,
                        Scene* scene = nullptr,
                        bool verbose = false
                    ); 
    
        ~Enemy();

        void UpdateMovement(float deltaTime, int steps = 1) override;



};


#endif //ENEMIES_H
