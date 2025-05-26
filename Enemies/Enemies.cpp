#include "Enemies.h"
#include "Scene.h"

Enemy::Enemy(QGraphicsItem* parent, QString filePath, QString entityType, Scene* scene, bool verbose)
    : Entity(parent, filePath, entityType, scene, verbose){ //Call entity for the scene !

    this->SetZombieStats(entityType);
    this->SetInternTimer(0);


    
}

Enemy::~Enemy() {
    if(parentScene) parentScene->currentEnemyCount--;
}


void Enemy::ChooseDestination(){

    if(this->GetEntityType() == "pZombie" && pDirectionDone == true){
        return; //We dont change anything in the direction
    }

    pDirectionDone = true;
    QPointF playerPos = parentScene->player->pos();
    QPointF enemyPos = this->pos();

    QPointF direction = playerPos - enemyPos; //Diff between the positions, will help us calculate the directions

    setTransformOriginPoint(pixmap().width() / 2.0, pixmap().height() / 2.0);
    qreal angle = std::atan2(direction.y(), direction.x()) * 180.0 / M_PI;

    if(this->Visual != nullptr){
        //this->Visual->setRotation(angle);
        this->setRotation(angle); //we move everything : since zombies are not affected by walls

    } else{ this->setRotation(angle); }


    qreal length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    if (length != 0) {
        direction /= length;
    }

    this->SetDirection(direction.x(), direction.y());
}


void Enemy::UpdateMovement(float deltaTime, int steps){

    float grace = GetInternTimer();
    if(this->GetHp() <= 0){
        this->TriggerDelete();
    }
    else if(grace > 0){
        grace -= deltaTime;
        if(grace < 0){
            grace = 0;
        }

        SetInternTimer(grace);
    }

    if(this->GetEntityType() == "spore"){
        if(this->spawningTimer <= 0){
            QPointF thisPos = this->GetRealCenter() - QPointF(100,100);
            parentScene->SpawnEnemies("runner", 2, thisPos, QPointF(200, 200), false);
            spawningTimer = baseSpawningTimer;
        } else {
            this->spawningTimer -= deltaTime;
        }

    } else if(this->GetEntityType() == "turret"){
        if(this->spawningTimer <= 0){
            QPointF thisPos = this->GetRealCenter() - QPointF(120,0);
            parentScene->SpawnEnemies("pZombie", 2, thisPos, QPointF(0, 120), false);
            thisPos = this->mapToScene(0,0) - QPointF(0,120);
            parentScene->SpawnEnemies("pZombie", 2, thisPos, QPointF(120, 0), false);
            spawningTimer = baseSpawningTimer;
        } else {
            this->spawningTimer -= deltaTime;
        }

    } else if(this->GetEntityType() == "mother"){
        QPointF thisPos;
        if(this->spawningTimer <= 0){
            thisPos = this->GetRealCenter();
            parentScene->SpawnEnemies("pZombie", 1, thisPos, QPointF(0, 120), false);
            spawningTimer = baseSpawningTimer;
        } else {
            this->spawningTimer -= deltaTime;
        }
        if(this->altSpawningTimer <= 0){
            thisPos = this->GetRealCenter();
            parentScene->SpawnEnemies("basic", 2, thisPos, QPointF(120, 120), false);
            altSpawningTimer = altBaseSpawningTimer;
        } else {
            this->altSpawningTimer -= deltaTime;
        }
    }

    this->ChooseDestination();

    Entity::UpdateMovement(deltaTime, steps);

}


void Enemy::SetZombieStats(QString type){ //Remember to add them and their hitbox in Scene::SpawnEnemies


    int speed = 1;
    int hp = 1;
    int damage = 1;
    float zGrace = 1; //The grace here is the grace they will apply to the player ; In another word, its their attack speed

    Entity* outfit = nullptr;

    // note that the outfit type is still zombie !!
    if(type == "runner"){
        outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/runner.png"),"runner", this->parentScene, this->IsVerbose());
        speed = 1500;
        hp = 50;
        damage = 5;
        zGrace = 0.3;
        givenScore = 10;
    }
    else if(type == "basic"){

        if (rand() % 100 == 0) {
            outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/secretBasic.png"),"basic", this->parentScene, this->IsVerbose());
        } else {
            outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/basic.png"),"basic", this->parentScene, this->IsVerbose());

        }

        speed = 350;
        hp = 350;
        damage = 20;
        zGrace = 1.5;
        givenScore = 5;

    }
    else if(type == "pZombie"){ //These are not really zombie, more of projectiles sent by zombie. Note that the hitbox is the same as runners
        outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/pZombie.png"),"pZombie", this->parentScene, this->IsVerbose());
        speed = 1500;
        hp = 2000;
        damage = 30;
        zGrace = 10;
    }
    else if(type == "spore"){ //Spores moove slowly and spawn runners, but they are not affected by environment. Good strat is melee them
        outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/spore.png"),"spore", this->parentScene, this->IsVerbose());
        speed = 100;
        hp = 1500;
        damage = 3;
        zGrace = 2;
        this->spawningTimer = 7;
        this->baseSpawningTimer = 7; //in seconds
        givenScore = 20;

    }
    else if(type == "turret"){ //Turret are fat zombies that shoots loads of projectiles. You need to aim at their eyes
        outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/turret.png"),"turret", this->parentScene, this->IsVerbose());
        speed = 200;
        hp = 1500;
        damage = 40;
        zGrace = 2;
        this->spawningTimer = 5;
        this->baseSpawningTimer = 5; //in seconds
        givenScore = 30;

    }
    else if(type == "mother"){ //Mother of all zombies !
        outfit = new Entity(this, QStringLiteral("../Resources/Textures/Cosmetics/Zombies/mother.png"),"mother", this->parentScene, this->IsVerbose());
        speed = 250;
        hp = 4000;
        damage = 40;
        zGrace = 1;
        this->spawningTimer = 0.5;
        this->baseSpawningTimer = 0.5; //in seconds
        this->altSpawningTimer = 7;
        this->altBaseSpawningTimer = 7; //in seconds
        givenScore = 100;

    }
    else {
        qDebug() << "⚠️ Unknown enemy type :" << type;
        throw std::runtime_error("❌ Failed to load enemy. The given type of the entity referenced before is wrong\n❌ You can add the type in Enemies.cpp in SetZombieStats");
    }


    this->SetBaseSpeed(speed);
    this->SetHp(hp);
    outfit->usualGrace = zGrace;
    outfit->SetDamages(damage);
    this->Visual = outfit;
    
}
