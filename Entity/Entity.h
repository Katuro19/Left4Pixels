#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QKeyEvent>

#include <iostream>
#include <string>  



class Entity : public QGraphicsPixmapItem {

public:
    Entity(QGraphicsItem* parent = nullptr, QString filePath = ""); //If filePath is null, will not load anything
    //virtual ~Entity();

private:

    int entityType;
    QString filePath;

    void LoadTexture(const QString &imagePath);
};


#endif //ENTITY_H
