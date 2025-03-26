#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>

#include "Entity.h"



class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(QObject* parent = nullptr);
    virtual ~Scene();

public slots:
    void update();


protected:
    QTimer* timer;
    void keyPressEvent(QKeyEvent* event);
    //void keyReleaseEvent(QKeyEvent* event);

private:
    QVector<Entity*> Entities;

    void LoadEntities();

};


#endif //SCENE_H
