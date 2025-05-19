#include "Saves.h"



void SaveGame(Scene *scene) {

    QString dir = QFileDialog::getExistingDirectory(nullptr, "Choisir un dossier de sauvegarde");
    QString save_file_name = QInputDialog::getText(nullptr,"Nom du fichier de sauvegarde","Entrez le nom de la sauvegarde (sans extension) :");
    QString fullpath = dir + "/" + save_file_name + ".json";

    FILE *file = fopen(fullpath.toStdString().c_str(), "w");
    if (file == nullptr) {
        qDebug() << "Erreur lors de l'ouverture du fichier de sauvegarde";
        return;
    }
    if (scene == nullptr) {
        qDebug() << "Erreur : la scène est nulle";
        fclose(file);
        return;
    }
    if (scene->player == nullptr) {
        qDebug() << "Erreur : le joueur est nul";
        fclose(file);
        return;
    }
    // On écrit les données de la scène dans le fichier
    fprintf(file, "{\n");
    fprintf(file, " \"Scene\": {\n");
    fprintf(file, "NB_Spawned_Entities : %d ,\n", scene->getSpawnedEntities());
    fprintf(file, "Is_Paused : %d\n", scene->getIsPaused());
    fprintf(file, "}\n");
    fprintf(file, " \"Map\": {\n");
    fprintf(file,  "Map_Name : %s\n",scene->getMapName().toStdString().c_str());
    fprintf(file, "Mode : %s\n",scene->getMode().toStdString().c_str());
    fprintf(file, "}\n");
    fprintf(file, " \"Player\": {\n");
    fprintf(file, "Player_pos (x,y) : (%.0f;%.0f),\n",scene->player->pos().x(),scene->player->pos().y());
    fprintf(file, "Cloth : %s,\n",scene->player->getCloth()->GetId().toStdString().c_str());
    fprintf(file, "}\n");
    fprintf(file, " \"Weapons\": {\n");
    for (unsigned int i = 0; i<3; i++){
        if (scene->player->getWeapon(i) == nullptr){
            continue;
        }
        fprintf(file, "Weapon_%d : %s,\n", i, scene->player->getWeapon(i)->GetId().toStdString().c_str());
        fprintf(file,"Magazine_%d: %d\n", i,scene->player->getWeapon(i)->GetMagazine());
    }
    fprintf(file, "}\n");
    fprintf(file, "}");
    fclose(file);
}
Scene* LoadSave() {

    Scene* scene = new Scene();

    QString fileName = QFileDialog::getOpenFileName(nullptr, "Selectioner la sauvegarde", "", "Tous les fichiers (*.json)");

    FILE *file = fopen(fileName.toStdString().c_str(), "r");
    if (file == nullptr) {
        qDebug() << "Erreur lors de l'ouverture du fichier de sauvegarde";
        return nullptr;
    }

    char line[256];

    int nb_spawned_entities = 0;
    int is_paused = 0;
    char map_name[128] = "";
    float player_pos_x = 0, player_pos_y = 0;
    char player_cloth[128] = "";

    char weapons[3][128] = { "", "", "" };
    int magazines[3] = { -1, -1, -1 };

    while (fgets(line, sizeof(line), file)) {
        // Nettoyage de fin de ligne
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' || line[len - 1] == ' ')) {
            line[--len] = '\0';
        }

        if (strstr(line, "NB_Spawned_Entities")) {
            sscanf(line, "NB_Spawned_Entities : %d", &nb_spawned_entities);
        } else if (strstr(line, "Is_Paused")) {
            sscanf(line, "Is_Paused : %d", &is_paused);
        } else if (strstr(line, "Map_Name")) {
            sscanf(line, "Map_Name : %127[^\n]", map_name);
        } else if (strstr(line, "Player_pos")) {
            sscanf(line, "Player_pos (x,y) : (%f;%f)", &player_pos_x, &player_pos_y);
        } else if (strstr(line, "Cloth")) {
            sscanf(line, "Cloth : %127[^,\n]", player_cloth);
        } else if (strstr(line, "Weapon")) {
            int index;
            char weapon_id[128];
            if (sscanf(line, "Weapon%d : %127[^,\n]", &index, weapon_id) == 2 && index >= 0 && index < 3) {
                strcpy(weapons[index], weapon_id);
            }
        } else if (strstr(line, "Magazine")) {
            int index, mag;
            if (sscanf(line, "Magazine%d: %d", &index, &mag) == 2 && index >= 0 && index < 3) {
                magazines[index] = mag;
            }
        }
    }

    fclose(file);

    return scene;
}