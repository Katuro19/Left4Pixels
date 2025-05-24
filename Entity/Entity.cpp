#include "Entity.h"
#include "Scene.h"


#define DEFAULT_PATH "../Resources/Textures/default.png"

QMap<QString, QPixmap> Entity::textureCache;
QMap<Entity* , float> Entity::graceTimers;


Entity::Entity(QGraphicsItem* parent,const QString filePath,const QString entityType, Scene* scene, bool verbose) : QGraphicsPixmapItem(parent), entityType(entityType), active(true), parentScene(scene), verbose(verbose){
    
    if(this->verbose)
        qDebug() << "🔄 Creating entity of type" << this->entityType << "...";

    if(!scene){
        throw std::runtime_error("❌ FATAL : no scene was defined in the declaration of this entity. Please check how you define this entity again.");
    }

    SetDefaultSpeed();



    if(!filePath.isEmpty()){
        this->LoadTexture(filePath);
    }


    // if(entityType == "cosmetic"){
    //     this->setScale(0.056);

    //     QPointF parentCenter = this->parentItem()->boundingRect().center();

    //     //this->setOffset(-1 * (this->boundingRect().center()));
    //     this->setPos(parentCenter - this->boundingRect().center());

    //     this->setTransformOriginPoint(this->boundingRect().center());

    // }
    
    if (this->parentItem()) {
        QPointF parentCenter = this->parentItem()->boundingRect().center();
        QPointF localCenter = this->mapFromItem(this->parentItem(), parentCenter);
        this->setTransformOriginPoint(localCenter);
    }

}


void Entity::LoadTexture(const QString &imagePath) {
    if (this->verbose)
        qDebug() << "🔁 Loading texture at" << imagePath;

    // Vérifie si la texture est déjà dans le cache
    if (!textureCache.contains(imagePath)) {
        QPixmap pixmap(imagePath);

        if (pixmap.isNull()) {
            if (this->verbose)
                qDebug() << "⚠️ Failed to load image:" << imagePath << "(Entity:" << this->identifier << ")";

            // Essaye de charger la texture par défaut
            QPixmap defaultPixmap(DEFAULT_PATH);
            if (defaultPixmap.isNull()) {
                throw std::runtime_error("❌ Couldn't load fallback texture at DEFAULT_PATH!");
            }

            // Met dans le cache pour plus tard
            textureCache.insert(imagePath, defaultPixmap);
        } else {
            textureCache.insert(imagePath, pixmap);
        }
    } else {
        if (this->verbose)
            qDebug() << "✅ Texture already in cache for:" << imagePath;
    }

    // Applique la texture (depuis le cache à coup sûr)
    setPixmap(textureCache[imagePath]);
}





void Entity::SetDefaultSpeed(){ //Set the default speed for basic entities
    if(this->entityType == "wall" || this->entityType == "item" || this->entityType == "tile" || this->entityType == "weapon" || this->entityType == "water" || this->entityType == "cosmetic" || this->entityType == "melee" || this->entityType == "zombie"){
        SetSpeed(0);
    }
    else if(this->entityType == "player"){
        SetSpeed(3.0);
    }
    else if(this->entityType == "runner" || this->entityType == "basic" || this->entityType == "pZombie"){
        SetSpeed(1.0);
    }
    else if(this->entityType == "projectile"){
        SetSpeed(5.0);
    }
    else {
        QString errorMessage = "❌ Entity type " + (this->entityType) + " does not exist or is not defined in Entity::SetDefaultSpeed()";
        throw std::runtime_error(errorMessage.toStdString());
    }
}



void Entity::UpdateMovement(float deltaTime, int steps){
/* How does the collisions work?

    - If the object is moving (mean it has a direction)
        -> For the coordinate X and Y separatly, will make it move by a certain number of steps (1 by default) and check everytime for collisions
        -> The coordinate will stop if a collision is detected, and stay at its current value

*/


    if(this->isMoving){

        this->SetSpeed(deltaTime * this->GetBaseSpeed()); //this set the speed based on the current framerate

        float entitySpeed = this->GetSpeed() * this->GetSpeedModifier();
        QPointF currentPos = pos(); //We get the current position
        QPointF currentDirection = this->GetDirection();
        QPointF XHolder(1,0);
        QPointF YHolder(0,1);
        QPointF nextPos = pos(); //We prepare the future position
        bool canMove;

        //First, for X
        for(float i=0 ; i < entitySpeed/steps; i++){ //Knowing that the number of pixel we are moving is direction * speed, we need to this for a number of times equal to the speed
            //qDebug() << "Speed :" << entitySpeed << "/ Steps :" << steps << "/ Ratio :" << entitySpeed/steps;
            QPointF currentMovement = XHolder * currentDirection.x();
            setPos(nextPos + currentMovement); //We are moving our character from 1 on X. Multiplying with GetDirection is useful if we are going backwards (negative numbers)
            canMove = !(this->PreventMovementCollision()); //We then check if we are having a collisions that's forbidden
            if(canMove){
                nextPos += currentMovement; //If we are allowed to move, we move one step forward
            }
            else{ //We are colliding smght : Lets stop the for() statement, because we hit a wall.
                break;
            }
        }


        setPos(currentPos); //Let's not forget to reset the position after testing on X

        //Same, but for the Y position
        for(float y=0 ; y < entitySpeed/steps; y++){
            QPointF currentMovement = YHolder * currentDirection.y();
            setPos(nextPos + currentMovement); 
            canMove = !(this->PreventMovementCollision());
            if(canMove){
                nextPos += currentMovement; 
            }
            else{
                break;
            }
        }

        if(this){
            this->setPos(nextPos); //Finally, we move !
        }
    }
    else{
        //If an Entity have no speed, that doesn't mean we should not check its collisions, except for things like walls or tiles !
        QString tempType = this->GetEntityType();

        if(tempType == "wall" || tempType == "tile" || tempType == "grid"){
            return;
        }


        this->PreventMovementCollision();

    }
}



bool Entity::PreventMovementCollision(){
    QList<QGraphicsItem *> collisions = this->collidingItems(); //We get all the collisions
    QString myType = this->GetEntityType();

    float defaultSpeedModifier = this->GetDefaultSpeedModifier();

    for (QGraphicsItem* item : collisions) {
        if (item->type() == Entity::Type) { //Check if its an entity, thanks to the preparations in Entity.h
            Entity* entity = static_cast<Entity*>(item); // We can cast here thanks to the type definition in the entity.h
            
            QString type = entity->GetEntityType(); //Grab what entity type we hit


            // qDebug() << "Me (" << this->GetId() << ") of type" << myType << "is colliding with" << entity->GetId() << "of type" << type;

            /* How to add a collision for a certain type :
                -> Add an elif case 
                -> Then in this elif, add if/else if case for differents type. Make sure to add them in the most common order for performances issues
            
            */

            if(myType == "player"){ //If this entity is a player
                //SetSpeed(GetBaseSpeed()); //We reset speed everytime
                if (type == "wall" || type == "grid") {
                    return true; //Can NOT move. the movement is PREVENTED !!
                } else if(type == "tile"){
                    this->SetSpeedModifier(defaultSpeedModifier);
                } else if (type=="water") { 
                    this->SetSpeedModifier(defaultSpeedModifier * 0.5); //50% speed debuff
                } else if (type == "item") {
                    //Do nothing, or do a special thing here like launching others functions, but it should never return false, only true, because if a wall is later in the list, we should not move !
                } else if (type == "basic" || type == "runner" || type == "pZombie"){
                    if(!graceTimers.contains(entity)){ //Grace: If the UID is still in the graceTimers list, it mean it shouldnt hit.
                        this->ReduceHp(entity->GetDamages());
                        //qDebug() << "Entity : " << entity->GetEntityType() << entity->GetDamages();
                        graceTimers[entity] = entity->usualGrace; //usual grace is mostly defined for enemies
                    }
                }
                
            }
            
            else if(myType == "runner" || myType == "basic"){
                if(type == "tile"){
                    this->SetSpeedModifier(defaultSpeedModifier);
                } else if(type == "wall"){
                    this->SetSpeedModifier(defaultSpeedModifier * 0.5); //50% speed debuff
                } else if(type == "player"){
                    return true;
                } else if(type == "projectile"){
                    if(GetInternTimer() <= 0){
                        this->ReduceHp(entity->GetDamages());
                        SetInternTimer(0.005); //Grace timer. Seems like nothing, but change everything
                    }
                } else if(type == "water"){
                    this->SetSpeedModifier(defaultSpeedModifier * 0.5); //50% speed debuff
                }
            }
            
            else if(myType == "pZombie"){
                if(type == "wall" || type == "player"){
                    this->TriggerDelete();
                }
            }

            else if(myType == "projectile"){
                if(type == "wall"){    
                    this->ReduceHp(10);

                } else if(type == "tile" || type == "water" || type == "grid"){
                    ;
                } else if(type == "runner"){
                    this->ReduceHp(1);

                }
            }
            

        }
    }

    return false; //if it went through every collision safely, return false, mean that we can move !!

}