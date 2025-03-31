#include "Entity.h"

#define DEFAULT_PATH "../Resources/Textures/default.png"



Entity::Entity(QGraphicsItem* parent, QString filePath, QString entityType) : QGraphicsPixmapItem(parent), entityType(entityType), active(true){
    qDebug() << "Creating entity of type" << this->entityType << "...";

    SetDefaultSpeed();

    if(!filePath.isEmpty()){
        this->LoadTexture(filePath);
    }

}



void Entity::LoadTexture(const QString &imagePath){
    qDebug() << "Loading texture at" << imagePath;

    QPixmap pixmap = QPixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Error loading image w/ path" << imagePath << ". (Entity" << this->identifier <<") FIX THE BUGS!";
        QPixmap defaultPixmap = QPixmap(DEFAULT_PATH);

        if(defaultPixmap.isNull()){
            throw std::runtime_error("Error loading default with path DEFAULT_PATH :(");

        }

        setPixmap(defaultPixmap);

    } 
    else {
        setPixmap(pixmap);
    }
}




void Entity::SetDefaultSpeed(){ //Set the default speed for basic entities
    if(this->entityType == "wall" || this->entityType == "tile"){
        SetSpeed(0);
    }
    else if(this->entityType == "player"){
        SetSpeed(3.0);
    }
    else if(this->entityType == "runner"){
        SetSpeed(1.0);
    }
    else {
        QString errorMessage = "Entity type " + (this->entityType) + " does not exist";
        throw std::runtime_error(errorMessage.toStdString());
    }
}