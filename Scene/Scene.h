#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QDateTime>


#include <vector>
#include <cmath>

#include "Entity.h"
#include "Player.h"
#include "MapLoader.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Scene(QObject* parent = nullptr);
    virtual ~Scene();

    Player* player;

    void CameraUpdate(Entity* entity) const;

    void AddEntity(Entity* entity, bool reposition = false, QPointF spawnLocation = QPointF(0,0));

    void SetPlayerPos(QPointF playerPos){
        this->player->setPos(playerPos);
    }

public slots:
    void update();


protected:
    QTimer* timer;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void UpdateDirection() const;
    int totalEntitySpawned = 0;


private:
    QVector<Entity*> Entities; //Will store every entity on the scene
    QSet<int> pressedKeys; //This is used for smooth movements


};


#endif //SCENE_H
