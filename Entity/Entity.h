#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QBitmap>
#include <QRegion>
#include <QPointF>


#include <iostream>
#include <string>  
#include <stdexcept>



class Entity : public QGraphicsPixmapItem {
/*
    Entity will be the parent for every object on the scene
        -> This is a QGraphicsPixmapItem.
            -> You can leave the filePath empty in the constructor to make an invisible entity.

        -> Every complex objects on the scene should be a child of Entity.

        -> Remember that attached children to an Entity are not loaded in the scene, they are loaded at the same time as their parent
            -> Their collision can be managed using a pointer (thats why you should make a child of entity) storing the children, then you can access it while checking collisions.
            -> The children B collision with an entity C not trigger if the parent A only is colliding with the entity C.
                -> Using pointers, with children from entity, you can detect the collision between B and C.

*/


public:
    Entity(QGraphicsItem* parent = nullptr, QString filePath = "", QString entityType = "wall");
    /*
        PARAMETERS :
        -> parent : decide who is the parent (another entity usually). Can be empty. note that this entity will be attached to the parent
            -> No need to load it, and will moove alongside the parent. Tho, collisions are separated.

        -> filePath : You can choose a filepath to immediatly load textures. If no path is given, will be invisible.


    */
    //virtual ~Entity();


    void TriggerVisibility(bool visible=true){
        this->setVisible(visible);
        this->active = visible;
    }

    void SetId(QString name){ //Set the ID.
        this->identifier = name;
    }

    void SetDirection(float dx, float dy, bool preventMoving=false){ //Save the direction and trigger isMoving. Using the preventMoving (to true) you can prevent the movement start
        this->direction = QPointF(dx, dy);
        if(!preventMoving){
            this->isMoving = true;
        }
    }

    QPointF GetDirection(){
        return this->direction;
    }

    void SetMovement(bool willMove){
        this->isMoving = willMove;
    }

    void UpdateMovement(){
        if(this->isMoving){
            setPos(pos() + direction * speed); //Move using current position + speed, use SetDirection
        }
    }

    bool IsMoving(){
        return this->isMoving;
    }

    void SetUid(int UID){
        this->uid = UID;
    };

    int GetUid(){
        return this->uid;
    }

    void SetSpeed(float newSpeed){
        this->speed = newSpeed;
    }

    float GetSpeed(){
        return this->speed;
    }

    QString GetEntityType(){
        return this->entityType;
    }

private:

    QString entityType; //Will be used to detect a collision type
    int uid; //uid, in case...
    QString identifier = "default_id"; //This is not a must have, its mostly for debug purpose and to know what object we are talking about

    QString filePath;
    bool active;

    bool perfectBox=false; //Will be used to decide about collisions : either perfect or big box. True mean perfect.
    QPainterPath cachedShape; //Special qpainter to save the shape collide box, since the collider wont change for a lot of entities.

    QPointF direction; //Direction can stock the 2D movement of an entity.
    bool isMoving=false; //Decide if an entity is mooving or no.
    float speed = 3.0; //Default speed

    void LoadTexture(const QString &imagePath); //Load the texture in path

    void SetDefaultSpeed();
};


#endif //ENTITY_H
