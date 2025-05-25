#ifndef SAVES_H
#define SAVES_H


#include <QInputDialog>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

#include "Scene.h"



void SaveGame(Scene *scene);
Scene* LoadSave();
QString GeSavedGamesPath();


#endif //SAVES_H
