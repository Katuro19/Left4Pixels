#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>


class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(QObject* parent = nullptr);
    virtual ~Scene();

public slots:
    void update();


protected:
    QTimer* timer;

private:
    QGraphicsTextItem* qgti;
    QGraphicsRectItem* qgri;

};


#endif //SCENE_H
