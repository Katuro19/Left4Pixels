#include "Entity.h"

#define DEFAULT_PATH "../Resources/Textures/default.png"



Entity::Entity(QGraphicsItem* parent, QString filePath) : QGraphicsPixmapItem(parent), entityType(0), active(true){
    qDebug() << "Creating entity...";

    if(!filePath.isEmpty()){
        this->LoadTexture(filePath);
    }

}



void Entity::LoadTexture(const QString &imagePath){
    cachedShape = QPainterPath(); //Empty the cache when reloading textures, so that the shape() call will rebound it


    qDebug() << "Loading texture at" << imagePath;

    QPixmap pixmap = QPixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Error loading image w/ path" << imagePath << ". (Entity" << this->identifier <<") FIX THE BUGS!";
        QPixmap defaultPixmap = QPixmap(DEFAULT_PATH);

        if(defaultPixmap.isNull()){
            qDebug() << "Error loading default with path DEFAULT_PATH :(";
        }

        setPixmap(defaultPixmap);

    } 
    else {
        setPixmap(pixmap);
    }
}

void Entity::ReloadEntity(){
        cachedShape = QPainterPath(); //Empty the cache, that mean the next shape() call will rebound the collisions (auto)
        qDebug() << "Shape cache emptied for entity" << this->identifier;

}


