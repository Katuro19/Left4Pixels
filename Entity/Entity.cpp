#include "Entity.h"

#define DEFAULT_PATH "../Resources/Textures/default.png"



Entity::Entity(QGraphicsItem* parent, QString filePath, int loadCollision) : QGraphicsPixmapItem(parent), entityType(0), active(true){
    qDebug() << "Creating entity...";

    if(!filePath.isEmpty()){
        this->LoadTexture(filePath);
    }

    if(loadCollision != 0){
        qDebug("Caching collision...");
        if(loadCollision == 2){
            this->perfectBox = true;
        }
    }
}




// QPainterPath Entity::shape() const {
//     if(!(this->cachedShape.isEmpty())){ //If the cached shape not empty, we don't reload !
//         qDebug() << "cached already for" << this->identifier;
//         return this->cachedShape;
//     }

//     QPainterPath path;

//     if (!this->perfectBox) { //Perfect is disabled : we load a big square
//         qDebug() << "big pp square" << this->identifier;
//         path =  QGraphicsPixmapItem::shape();  // Launch basic shape doing a big box around the item
//         this->cachedShape = path;
//         return path;
//     }

//     //For the pixel Perfect
//     qDebug() << "pixel perfect for" << this->identifier;


//     QBitmap mask = pixmap().mask();
//     QRegion region(mask);
    
//     // Boucle à travers les pixels dans le rectangle englobant de la région
//     QRect boundingRect = region.boundingRect();
//     for (int y = boundingRect.top(); y < boundingRect.bottom(); ++y) {
//         for (int x = boundingRect.left(); x < boundingRect.right(); ++x) {
//             if (region.contains(QPoint(x, y))) {
//                 path.addRect(QRect(x, y, 1, 1));  // Ajoute chaque pixel comme un petit rectangle
//             }
//         }
//     }
//     this->cachedShape = path;
//     return path;
// }




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


