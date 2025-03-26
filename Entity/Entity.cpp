#include "Entity.h"

#define DEFAULT_PATH "../Resources/Textures/default.png"



Entity::Entity(QGraphicsItem* parent, QString filePath) : QGraphicsPixmapItem(parent), entityType(0), filePath(""){
    qDebug() << "trying load " << filePath << " . FIX THE BUGS!";

    if(!filePath.isEmpty()){
        this->LoadTexture(filePath);
    }
}



void Entity::LoadTexture(const QString &imagePath){

    QPixmap pixmap = QPixmap(imagePath);
    if (pixmap.isNull()) { //Check that it is loaded
        qDebug() << "Error loading image w/ path " << imagePath << " . FIX THE BUGS!";
        QPixmap defaultPixmap = QPixmap(DEFAULT_PATH);
        if(defaultPixmap.isNull()){
            qDebug() << "Error loading default with path DEFAULT_PATH :(";
        }
        setPixmap(defaultPixmap);
    } else {
        setPixmap(pixmap);
    }
}