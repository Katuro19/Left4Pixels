#ifndef SAVES_H
#define SAVES_H
#include "Scene.h"
#include <QFileDialog>


class Saves {
public:
    void SaveGame(Scene *scene);
    Scene LoadSave();
};



#endif //SAVES_H
