#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "Entity.h"

#include <random>


class Projectile : public Entity {
    private:
        bool isBreakable;
        int pierces;
        int bounces;
        QPointF target;
        QPointF startPos;
        float spread;

    public:
        explicit Projectile(QGraphicsItem* parent = nullptr,
            QString filePath = "",
            QString entityType = "projectile",
            QPointF target = {0, 0},
            QPointF startPos = {0, 0},
            int damage = 10,
            bool isBreakable = true,
            int pierces = 0,
            int bounces = 0,
            int HP = 1,
            float speed = 1,
            float spread = 0,
            Scene* scene = nullptr,
            bool verbose = false);  // Ajout de Scene* comme paramètre

        ~Projectile(){
            //qDebug() << "Projectile: Destructor called";
        }


        void setStartingPos(QPointF pos);
        QPointF getStartingPos() const;

        bool getBreakable() const;
        void setBreakable(bool isBreakable);

        int getPierces() const;
        void setPierces(int pierces);

        int getBounces() const;
        void setBounces(int bounces);

        QPointF getTarget() const;
        void setTarget(QPointF target);

        void updateDirection();

        void UpdateMovement(float deltaTime, int steps = 1) override;

        void Reset(QPointF newTarget, QPointF newStartPos, int damage, int hp, float speed, float spread);
    
};

#endif //PROJECTILES_H
