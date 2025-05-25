#include "Saves.h"




void SaveGame(Scene *scene) {
    QString dir = QFileDialog::getExistingDirectory(nullptr, "Choisir un dossier de sauvegarde");
    if (dir.isEmpty()) {
        qDebug() << "Aucun dossier sélectionné";
        return;
    }

    QString save_file_name = QInputDialog::getText(nullptr, "Nom du fichier de sauvegarde", "Entrez le nom de la sauvegarde (sans extension) :");
    if (save_file_name.isEmpty()) {
        qDebug() << "Aucun nom de fichier saisi";
        return;
    }

    QString fullpath = dir + "/" + save_file_name + ".json";

    if (scene == nullptr) {
        qDebug() << "Erreur : la scène est nulle";
        return;
    }
    if (scene->player == nullptr) {
        qDebug() << "Erreur : le joueur est nul";
        return;
    }

    // Construction de l'objet JSON principal
    QJsonObject rootObject;

    qDebug() << "Saving scene data to" << fullpath;

    // Données de la scène
    QJsonObject sceneObject;
    sceneObject["NB_Spawned_Entities"] = scene->GetSpawnedEntities();
    sceneObject["Is_Paused"] = !(scene->GetIsPaused());
    rootObject["Scene"] = sceneObject;

    qDebug() << "Saving map data...";

    // Données de la carte
    QJsonObject mapObject;
    mapObject["Map_Name"] = scene->GetMapName();
    mapObject["Mode"] = scene->GetMode();
    rootObject["Map"] = mapObject;

    qDebug() << "Saving player data...";

    // Données du joueur
    QJsonObject playerObject;
    playerObject["Player_pos_x"] = static_cast<int>(scene->player->pos().x());
    playerObject["Player_pos_y"] = static_cast<int>(scene->player->pos().y());
    playerObject["Cloth"] = scene->player->GetCloth()->GetId();
    rootObject["Player"] = playerObject;

    qDebug() << "Saving weapons...";

    // Données des armes
    QJsonObject weaponsObject;
    for (unsigned int i = 0; i < 3; i++) {
        QString weaponKey = QString("Weapon_%1").arg(i);
        QString magazineKey = QString("Magazine_%1").arg(i);

        if (scene->player->GetWeapon(i) == nullptr) {
            weaponsObject[weaponKey] = "null";
            weaponsObject[magazineKey] = "null";
        } else {
            weaponsObject[weaponKey] = scene->player->GetWeapon(i)->GetName();
            weaponsObject[magazineKey] = scene->player->GetWeapon(i)->GetMagazine();
        }
    }
    rootObject["Weapons"] = weaponsObject;

    // Création du document JSON et écriture dans le fichier
    QJsonDocument jsonDoc(rootObject);

    QFile file(fullpath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Erreur lors de l'ouverture du fichier de sauvegarde:" << fullpath;
        return;
    }

    file.write(jsonDoc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Sauvegarde terminée dans" << fullpath;
}




Scene* LoadSave() {

    QString fullpath = QFileDialog::getOpenFileName(nullptr,"Sélectionner la sauvegarde", GeSavedGamesPath(),"Tous les fichiers (*.json)");


    if (fullpath.isEmpty()) {
        qDebug() << "Aucun fichier sélectionné";
        return nullptr;
    }
    QFile file(fullpath);


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur: impossible d'ouvrir le fichier" << fullpath;
        return nullptr;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Erreur de parsing JSON:" << parseError.errorString();
        return nullptr;
    }

    Scene* scene= new Scene(nullptr);

    QPointF playerPos(0, 0);

    QJsonObject rootObject = jsonDoc.object();

    // Lecture des données de la scène
    if (rootObject.contains("Scene")) {

        QJsonObject sceneObject = rootObject["Scene"].toObject();

        int nbSpawnedEntities = sceneObject["NB_Spawned_Entities"].toInt();
        bool isPaused = sceneObject["Is_Paused"].toBool();

        qDebug() << "Chargement scène - Entités:" << nbSpawnedEntities << "Pause:" << isPaused;

        scene->SetSpawnedEntities(nbSpawnedEntities);
        scene->SetIsPaused(isPaused);
    }



    // Lecture des données du joueur
    if (rootObject.contains("Player")) {

        QJsonObject playerObject = rootObject["Player"].toObject();

        int playerPosX = playerObject["Player_pos_x"].toInt();
        int playerPosY = playerObject["Player_pos_y"].toInt();
        QString cloth = playerObject["Cloth"].toString();

        qDebug() << "Chargement joueur - Position:" << playerPosX << "," << playerPosY << "Vêtement:" << cloth;

        Player* player = new Player(nullptr,QStringLiteral("../Resources/Textures/Characters/Player/player.png"),"player",1.0,scene,true);

        scene->player = player;
        playerPos = QPointF(playerPosX, playerPosY);
        scene->player->setPos(playerPosX, playerPosY);
        scene->SetPlayerPos(QPointF(playerPosX, playerPosY));

        // Charger le vêtement du joueur


        QString outfit_texturePath = QString("../Resources/Textures/Cosmetics/Player/%1.png").arg(cloth);
        (*player).SetId("Cube");
        Entity* outfit = new Entity(scene->player,outfit_texturePath,"cosmetic", scene);
        (*outfit).SetId(cloth);
        scene->player->SetCloth(outfit);

    }

    // Lecture des données des armes
    if (rootObject.contains("Weapons")) {

        QJsonObject weaponsObject = rootObject["Weapons"].toObject();

        qDebug() << "Chargement des armes...";

        for (int i = 0; i < 3; i++) {
            QString weaponKey = QString("Weapon_%1").arg(i);
            QString magazineKey = QString("Magazine_%1").arg(i);

            if (weaponsObject.contains(weaponKey) && weaponsObject.contains(magazineKey)) {
                QString weaponName = weaponsObject[weaponKey].toString();

                if (weaponName == "null") {
                    qDebug() << "Arme" << i << ": aucune";
                    scene->player->SetWeapon( nullptr, i, nullptr);
                } else {
                    int magazine = weaponsObject[magazineKey].toInt();
                    qDebug() << "Arme" << i << ":" << weaponName << "Munitions:" << magazine;

                    QString weapon_texturePath = QString("../Resources/Textures/Weapons/Hands/%1.png").arg(weaponName);

                    Weapon* weapon = new Weapon(scene->player,weapon_texturePath,"weapon", scene, 10, false);

                    weapon->SetMagazine(magazine);
                    scene->player->SetWeapon(weapon, i, weaponName);
                }
            }
        }
    }

    // Lecture des données de la carte
    if (rootObject.contains("Map")) {

        QJsonObject mapObject = rootObject["Map"].toObject();

        QString mapName = mapObject["Map_Name"].toString();
        QString mode = mapObject["Mode"].toString();

        qDebug() << "Chargement carte - Nom:" << mapName << "Mode:" << mode;

        scene->SetMapName(mapName);
        scene->SetMode(mode);

        new MapLoader(scene->GetMapName(), *scene);
    }

    scene->SetPlayerPos(playerPos);

    qDebug() << "Chargement terminé depuis" << fullpath;

    return scene; // Retourner la scène chargée
}


QString GeSavedGamesPath() {

    // This function returns the path to the Saved Games directory for Windows users in WSL.
    QDir usersDir("/mnt/c/Users");
    QStringList users = usersDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &user : users) {
        if (user != "Default" && user != "Public" && user != "All Users" && user != "Default User") {
            QString testPath = "/mnt/c/Users/" + user + "/Saved Games";
            if (QDir(testPath).exists()) {
                return testPath;
            }
        }
    }

    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}