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
public:
    Projectile(QGraphicsItem* parent = nullptr, const QString filePath = "", const QString entityType = "projectile",  QPointF target = {0,0}, int damage = 10, bool isBreakable = true, int pierces = 0,int bounces = 0, int HP = 50, float speed = 1);

    ~Projectile();

    void setDamage(int damage);
    int getDamage() const;

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


};

#endif //PROJECTILES_H
