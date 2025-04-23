#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "Entity.h"



class Projectile : public Entity {
    private:
        int damage;
        bool isBreakable;
        int pierces;
        int bounces;
        int HP;
        float speed;
        QPointF target;
        QPointF startPos;

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
            int HP = 50,
            float speed = 1,
            Scene* scene = nullptr);  // Ajout de Scene* comme paramètre

        ~Projectile(){
            qDebug() << "Projectile delete debug";
        }

        void setDamage(int damage);
        int getDamage() const;

        void setStartingPos(QPointF pos);
        QPointF getStartingPos() const;

        bool getBreakable() const;
        void setBreakable(bool isBreakable);

        int getPierces() const;
        void setPierces(int pierces);

        int getBounces() const;
        void setBounces(int bounces);

        int getHP() const;
        void setHP(int HP);

        QPointF getTarget() const;
        void setTarget(QPointF target);

        void updateDirection();

        void UpdateMovement(float deltaTime, int steps = 1) override;

};

#endif //PROJECTILES_H
