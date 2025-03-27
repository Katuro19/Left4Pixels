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

#include <iostream>
#include <string>  



class Entity : public QGraphicsPixmapItem {
/*
    Entity will be the parent for every object on the scene
        -> This is a QGraphicsPixmapItem.
            -> You can leave the filePath empty in the constructor to make an invisible entity.

        -> Collision will be OFF by default. 
            -> If you trigger it (loadCollisions to true), the default hitbox will be cached as pixel perfect on the default loaded sprite.

        -> Every complex objects on the scene should be a child of Entity.

        -> Remember that attached children to an Entity are not loaded in the scene, they are loaded at the same time as their parent
            -> Their collision can be managed using a pointer (thats why you should make a child of entity) storing the children, then you can access it while checking collisions.
            -> The children B collision with an entity C not trigger if the parent A only is colliding with the entity C.
                -> Using pointers, with children from entity, you can detect the collision between B and C.

*/


public:
    Entity(QGraphicsItem* parent = nullptr, QString filePath = "", int loadCollisions = 0);
    /*
        PARAMETERS :
        -> parent : decide who is the parent (another entity usually). Can be empty. note that this entity will be attached to the parent
            -> No need to load it, and will moove alongside the parent. Tho, collisions are separated.

        -> filePath : You can choose a filepath to immediatly load textures. If no path is given, will be invisible.

        -> loadCOllisions : Different parameters doing different things
            -> 0 : No collisions nor shape constructors will be loaded (default should be used)
            -> 1 : Load collisions as a simple object (use it for bg texture for exemple)
            -> 2 : Load collisions as pixel perfect (use it for complex objects)

    */
    //virtual ~Entity();


    void TriggerVisibility(bool visible=true){
        this->setVisible(visible);
        this->active = visible;
    }

    void SetId(QString name){
        this->identifier = name;
    }

    // QPainterPath shape() const; 


private:

    int entityType;
    QString identifier = "default_id"; //This is not a must have, its mostly for debug purpose and to know what object we are talking about

    QString filePath;
    bool active;

    bool perfectBox=false; //Will be used to decide about collisions : either perfect or big box. True mean perfect.
    QPainterPath cachedShape; //Special qpainter to save the shape collide box, since the collider wont change for a lot of entities.


    void LoadTexture(const QString &imagePath); //Load the texture in path
    void ReloadEntity(); //Reload the entity colliders.
};


#endif //ENTITY_H
