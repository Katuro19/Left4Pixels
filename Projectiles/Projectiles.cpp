#include "Projectiles.h"
#include "Scene.h"

Projectile::Projectile(QGraphicsItem* parent, QString filePath, QString entityType,
    QPointF target, QPointF startPos, int damage, bool isBreakable,
    int pierces, int bounces, int HP, float speed, float spread, Scene* scene, bool verbose)
    : Entity(parent, filePath, entityType, scene, verbose),  isBreakable(isBreakable), pierces(pierces),bounces(bounces), target(target), startPos(startPos)  // Auto call of entity for the scene !
{

    this->spread = spread;
    this->setPos(startPos);

    this->SetBaseSpeed(speed);
    this->SetHp(HP);


    this->SetDamages(damage);

    this->UpdateDirection();
}


void Projectile::SetBreakable(const bool isBreakable) {
    this->isBreakable = isBreakable;
}
void Projectile::SetPierces(const int pierces) {
    this->pierces = pierces;
}
void Projectile::SetBounces(const int bounces) {
    this->bounces = bounces;
}
void Projectile::SetTarget(const QPointF target) {
    this->target = target;
}
bool Projectile::GetBreakable() const {
    return this->isBreakable;
}
int Projectile::GetPierces() const {
    return this->pierces;
}
int Projectile::GetBounces() const {
    return this->bounces;
}

QPointF Projectile::GetTarget() const {
    return this->target;
}

void Projectile::SetStartingPos(QPointF pos) {
    this->startPos = pos;
}
QPointF Projectile::GetStartingPos() const {
    return this->startPos;
}

void Projectile::UpdateDirection() {

    QPointF realPos = this->GetRealCenter(); //We get the real center, not the sprite start

    qreal angle = std::atan2(target.y() - realPos.y(), target.x() - realPos.x()); //We calculate the angle and then convert it into °
    qreal baseDegrees = angle * 180.0 / M_PI;

    //We calculate the spread
    qreal spreadOffset = 0.0;
    if (this->spread > 0.0) {
        spreadOffset = ((static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f) * this->spread;
    }

    // We add the angle and the spread together
    qreal finalDegrees = baseDegrees + spreadOffset;

    // Convert to radiants
    qreal finalRadians = finalDegrees * M_PI / 180.0;
    QPointF direction(std::cos(finalRadians), std::sin(finalRadians));

    //qDebug() << "Direction : x =" << direction.x() << ", y = " << direction.y();
    this->SetDirection(direction.x(),direction.y());
    this->setTransformOriginPoint(pixmap().width() / 2.0, pixmap().height() / 2.0);
    this->setRotation(finalDegrees);

}


void Projectile::UpdateMovement(float deltaTime, int steps){
    if(this->GetSpeed() == 0){
        return;
    }

    QRectF sceneBounds = this->parentScene->sceneRect(); // taille logique de la scène
    QRectF itemBounds = this->sceneBoundingRect();

    if (!sceneBounds.intersects(itemBounds)) {this->SetHp(0);}


    float cooldownTimer = GetInternTimer() - deltaTime; //Only deltaTime because nothing affects the projectile
    SetInternTimer(cooldownTimer);

    if (GetInternTimer() <= 0.0f) {
        this->ReduceHp(); //We remove HP every second

        float cooldownSecs = 0.05f; //small cooldown before loosing HP again

        SetInternTimer(cooldownSecs);

    }

    //qDebug() << this->HP;
    if(this->HP <= 0){
        this->setVisible(false); // cache-le au lieu de delete
        this->SetHp(0);  
        this->SetBaseSpeed(0);
        //this->TriggerDelete();
        //parentScene->DeleteEntity(this);

    } else {
        //qDebug() << "Projectile pos =" << this->pos() << " target =" << this->target;
        this->ReduceHp(10);
        Entity::UpdateMovement(deltaTime, steps);
    }
}

void Projectile::Reset(QPointF newTarget, QPointF newStartPos, int damage, int hp, float speed, float spread) {
    this->target = newTarget;
    this->startPos = newStartPos;
    this->SetDamages(damage);
    this->SetHp(hp);
    this->SetBaseSpeed(speed);
    this->spread = spread;

    this->setPos(newStartPos);
    this->setVisible(true);
    this->UpdateDirection();
}
