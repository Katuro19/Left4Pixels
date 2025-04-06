#include "Entity.h"

#define DEFAULT_PATH "../Resources/Textures/default.png"



Entity::Entity(QGraphicsItem* parent,const QString filePath,const QString entityType) : QGraphicsPixmapItem(parent), entityType(entityType), active(true){
    qDebug() << "Creating entity of type" << this->entityType << "...";

    SetDefaultSpeed();

    if(!filePath.isEmpty()){
        this->LoadTexture(filePath);
    }

}



void Entity::LoadTexture(const QString &imagePath){
    qDebug() << "Loading texture at" << imagePath;

    QPixmap pixmap = QPixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Error loading image w/ path" << imagePath << ". (Entity" << this->identifier <<") FIX THE BUGS!";
        QPixmap defaultPixmap = QPixmap(DEFAULT_PATH);

        if(defaultPixmap.isNull()){
            throw std::runtime_error("Error loading default with path DEFAULT_PATH :(");

        }

        setPixmap(defaultPixmap);

    } 
    else {
        setPixmap(pixmap);
    }
}




void Entity::SetDefaultSpeed(){ //Set the default speed for basic entities
    if(this->entityType == "wall" || this->entityType == "item" || this->entityType == "tile" || this->entityType == "weapon" ){
        SetSpeed(0);
    }
    else if(this->entityType == "player"){
        SetSpeed(3.0);
    }
    else if(this->entityType == "runner"){
        SetSpeed(1.0);
    }
    else {
        QString errorMessage = "Entity type " + (this->entityType) + " does not exist";
        throw std::runtime_error(errorMessage.toStdString());
    }
}



void Entity::UpdateMovement(int steps){
/* How does the collisions work?

    - If the object is moving (mean it has a direction)
        -> For the coordinate X and Y separatly, will make it move by a certain number of steps (1 by default) and check everytime for collisions
        -> The coordinate will stop if a collision is detected, and stay at its current value

*/
    if(this->isMoving){

        QPointF currentPos = pos(); //We get the current position
        QPointF currentDirection = this->GetDirection();
        QPointF XHolder(1,0);
        QPointF YHolder(0,1);
        QPointF nextPos = pos(); //We prepare the future position
        float entitySpeed = this->GetSpeed();
        bool canMove;

        //First, for X
        for(int i=0 ; i < entitySpeed; i++){ //Knowing that the number of pixel we are moving is direction * speed, we need to this for a number of times equal to the speed
            QPointF currentMovement = XHolder * currentDirection.x();
            setPos(nextPos + currentMovement); //We are moving our character from 1 on X. Multiplying with GetDirection is useful if we are going backwards (negative numbers)
            canMove = !(this->PreventMovementCollision()); //We then check if we are having a collisions thats forbiden
            if(canMove){
                nextPos += currentMovement ; //If we are allowed to move, we move one step forward
            }
            else{ //We are colliding smght : Lets stop the for() statement, because we hit a wall.
                break;
            }
        }


        setPos(currentPos); //Let's not forget to reset the position after testing on X

        //Same, but for the Y position
        for(int y=0 ; y < entitySpeed; y++){
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

    
        this->setPos(nextPos); //Finally, we move !
    }
}



bool Entity::PreventMovementCollision(){
    QList<QGraphicsItem *> collisions = this->collidingItems(); //We get all the collisions

    for (QGraphicsItem* item : collisions) {
        if (item->type() == Entity::Type) { //Check if its an entity, thanks to the preparations in Entity.h
            Entity* entity = static_cast<Entity*>(item); // We can cast here thanks to the type definition in the entity.h
    
            QString type = entity->GetEntityType(); //Grab what entity type we hit
            QString myType = this->GetEntityType();

            /* How to add a collision for a certain type :
                -> Add an elif case 
                -> Then in this elif, add if/else if case for differents type. Make sure to add them in the most common order for performances issues
            
            */

            if(myType == "player"){ //If this entity is a player
                if (type == "wall") {
                    return true; //Can NOT move. the movement is PREVENTED !!
                } else if (type == "item") {
                    //Do nothing, or do a special thing here like launching others functions, but it should never return false, only true, because if a wall is later in the list, we should not move !
                }
            }
            
            else if(myType == "runner"){
                if(type == "wall"){
                    return true;
                }
            }

        }
    }

    return false; //if it went through every collisions safely, return false, mean that we can move !!

}