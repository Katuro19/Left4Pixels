#ifndef MAPLOADER_H
#define MAPLOADER_H


#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>

#include <QString>

#include "Entity.h"
#include "Scene.h"

class Scene; //Forward declaration because of loop imports !


class MapLoader{

    public :

        MapLoader(QString mapName, Scene &scene);
   
        ~MapLoader();
    
    private :
        void ReadMapFile(std::string mapName);
        void PlaceTile(QString tileType, QString tileName, int xPos, int yPos);

        int textureSize = 64; //If your texture size change, you can change this number

        Scene &mainScene;
};


#endif //MAPLOADER_H
