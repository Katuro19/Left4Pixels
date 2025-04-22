#include "MapLoader.h"


MapLoader::MapLoader(QString mapName, Scene &scene) : mainScene(scene){ 
    qDebug() << "-------------------------------------------------------------------";
    qDebug() << "Now loading" << mapName;
    ReadMapFile(mapName.toStdString());
    qDebug() << "End of map loading";
    qDebug() << "-------------------------------------------------------------------";
}


void MapLoader::ReadMapFile(std::string mapName){ //WARNING : this only work for square textures !!

    int mapSizeX;
    int mapSizeY;
    std::string line;
    int spawnX;
    int spawnY;

    std::ifstream config("../Resources/Maps/" + mapName + "/config.txt"); //Open the map
    if(config.peek() == std::ifstream::traits_type::eof()){
        config.close();
        throw std::runtime_error("Error loading map " + mapName + ": config.txt is empty.");

    }

    getline(config, line);
    config.close(); // we can close since there's only one line !

    std::istringstream issconfig(line);
    std::string token;
    int count = 0;

    //We know there's only 4 elements
    while (issconfig >> token) {
        if(count == 0)
            mapSizeX = std::stoi(token);
        else if(count == 1)
            mapSizeY = std::stoi(token);
        else if(count == 2)
            spawnX = std::stoi(token);
        else if(count == 3)
            spawnY = std::stoi(token);

        count++;
    }

    //qDebug() << mapSizeX << mapSizeY << spawnX << spawnY;


    std::ifstream file("../Resources/Maps/" + mapName + "/map.txt"); //Open the map


    if (!file.is_open()) {
        throw std::runtime_error("Error loading map " + mapName + ", probably path?");
    }

    QString firstPart;
    QString secondPart;
    QPointF tilePosition = QPointF(0,0); //Used to place the tile
    int tileNumber = 1; //Keep a track of where we are in the current map : for exemple, if the map is 10 * 10 tiles, when this number is 10, we increase y by tje texture size !
    QString qStringToken;
    int xCounter = 0;
    int yCounter = 0;

    // Read line by line
    while (std::getline(file, line)) {
        // Get all the token on one line
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) { //This line read (>>) the token in the input stream, and while there's token, we continue to read.

            qStringToken = QString::fromStdString(token);
            firstPart = qStringToken.left(1);
            secondPart = qStringToken.mid(1); //These two lines cut the token in two, the type (wall, tile, water, ...) and the code (00, A0, ...)
            
            try{
                PlaceTile(firstPart, secondPart, xCounter * this->textureSize, yCounter * this->textureSize); //Dont forget to multiply here !
            }
            catch(const std::runtime_error& e){
                file.close();
                throw std::runtime_error(e.what());
            }

            tileNumber++;
            xCounter++;
            if(xCounter >= mapSizeX){ //if our x counter is equal to the map size, we increase the y counter !
                yCounter++;
                xCounter = 0; //Dont forget this !
            }
        }
    }

    file.close();
    mainScene.SetPlayerPos(QPointF(spawnX * this->textureSize, spawnY * this->textureSize));
}


void MapLoader::PlaceTile(QString tileType, QString tileName, int xPos, int yPos){
    QString entityType;
    QPointF futurePos = QPointF(xPos, yPos);
    //qDebug() << tileType << tileName;


    if(tileType == "w"){
        entityType = "wall";
    }
    else if(tileType == "t"){
        entityType = "tile";
    }
    else if(tileType == "a"){
        entityType = "water";
    }
    else{
        throw std::runtime_error("Error loading tiles: tile type " + tileType.toStdString() + " does not exist or is not defined in MapLoader::PlaceTile.");
    }

    std::string path = "../Resources/Textures/Tiles/" + tileName.toStdString();
    Entity* toSpawn = new Entity(nullptr,QString::fromStdString(path),entityType, &mainScene);
    //toSpawn->setPos(futurePos);
    this->mainScene.AddEntity(toSpawn, true, futurePos);

}
