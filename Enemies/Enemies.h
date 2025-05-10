#ifndef ENEMIES_H
#define ENEMIES_H

#include "Entity.h"
#include "Scene.h"


class Scene; //Forward declaration


class Enemy : public Entity {
    private:

    
    public:
        // Constructeur de Player
        explicit Enemy(QGraphicsItem* parent = nullptr,
                        QString filePath = "",
                        QString entityType = "runner",
                        Scene* scene = nullptr,
                        bool verbose = false); 
    
    ~Enemy();



};


#endif //ENEMIES_H
