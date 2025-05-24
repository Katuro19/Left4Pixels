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


        void SetStartingPos(QPointF pos);
        QPointF GetStartingPos() const;

        bool GetBreakable() const;
        void SetBreakable(bool isBreakable);

        int GetPierces() const;
        void SetPierces(int pierces);

        int GetBounces() const;
        void SetBounces(int bounces);

        QPointF GetTarget() const;
        void SetTarget(QPointF target);

        void UpdateDirection();

        void UpdateMovement(float deltaTime, int steps = 1) override;

        void Reset(QPointF newTarget, QPointF newStartPos, int damage, int hp, float speed, float spread);
    
};

#endif //PROJECTILES_H
