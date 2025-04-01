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
    void setBreakble(bool isBreakble);
    void setPeirces(int peirces);
    void setBounces(int bounces);
    void setHP(int HP);
    void setTarget(QPointF target);
    int getDamage() const;
    bool getBreakble() const;
    int getPeirces() const;
    int getBounces() const;
    int getHP() const;
    QPointF getTarget() const;
};

#endif //PROJECTILES_H
