#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "Entity.h"

class Projectile : public Entity {
private:
    int damage;
    bool isBreakble;
    int peirces;
    int bounces;
    int HP;
    QPointF target;
public:
    Projectile(QGraphicsItem* parent = nullptr, QString filePath = "", QString entityType = "projectile", int damage = 10, bool isBreakble = true, int peirces = 0,int bounces = 0, int HP = 50, QPointF target = {0,0});

    ~Projectile();

    void setDamage(int damage);
    int getDamage() const;

    bool getBreakble() const;
    void setBreakble(bool isBreakble);

    int getPierces() const;
    void setPierces(int peirces);

    int getBounces() const;
    void setBounces(int bounces);

    int getHP() const;
    void setHP(int HP);

    QPointF getTarget() const;
    void setTarget(QPointF target);


};

#endif //PROJECTILES_H
