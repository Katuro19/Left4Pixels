#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QGraphicsView>

#include "Entity.h"
#include "Player.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(QObject* parent = nullptr);
    virtual ~Scene();

    Player* player;

    void CameraUpdate(Entity* entity);



public slots:
    void update();


protected:
    QTimer* timer;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void UpdateDirection();
    void ProvidePlayerMovement(Entity* entity, QPointF nextPositionX, QPointF nextPositionY);


private:
    QVector<Entity*> Entities; //Will store every entities on the scene
    void LoadEntities(); //Load entities
    QSet<int> pressedKeys; //This is used for smooth movements

};


#endif //SCENE_H
