#include "Saves.h"
#include <QInputDialog>


void Saves::SaveGame(Scene *scene) {
    QString dir = QFileDialog::getExistingDirectory(nullptr, "Choisir un dossier de sauvegarde");
    QString save_file_name = QInputDialog::getText(nullptr,"Nom du fichier de sauvegarde","Entrez le nom de la sauvegarde (sans extension) :");
    QString fullpath = dir + "/" + save_file_name + ".json";

    FILE *file = fopen(fullpath.toStdString().c_str(), "w");
    if (file == nullptr) {
        qDebug() << "Erreur lors de l'ouverture du fichier de sauvegarde";
        return;
    }
    // On écrit les données de la scène dans le fichier
    fprintf(file, "{\n");
    fprintf(file, " \"Scene\": {\n");
    fprintf(file, scene->getSpawnedEntities() + ",\n");
    fprintf(file, scene->getIsPaused() + "\n");
    fprintf(file, "}\n");
    fprintf(file, " \"Map\": {\n");
    fprintf(file,  "%s\n",scene->getMapName().toStdString().c_str());
    fprintf(file, "}\n");
    fprintf(file, " \"Player\": {\n");
    fprintf(file, "(%.0f;%.0f),\n",scene->player->pos().x(),scene->player->pos().y());
   //fprintf(file, "%s,\n",scene->player->getCloth().toStdString().c_str());
    fprintf(file, "\n");
    fprintf(file, "}\n");
    fprintf(file, " \"Weapon\": {\n");
    fprintf(file, "%s,\n", scene->player->getWeapon()->GetName().toStdString().c_str());
    fprintf(file, "%d\n", scene->player->getWeapon()->GetMagazine());
    fprintf(file, "}\n");





}
Scene Saves::LoadSave() {

    Scene* scene = new Scene();

    QString fileName = QFileDialog::getOpenFileName(nullptr, "Selectioner la sauvegarde", "", "Tous les fichiers (*.json)");




}