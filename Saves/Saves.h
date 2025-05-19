#ifndef SAVES_H
#define SAVES_H


#include <QInputDialog>
#include <QFileDialog>

#include "Scene.h"



void SaveGame(Scene *scene);
Scene* LoadSave();

#endif //SAVES_H
