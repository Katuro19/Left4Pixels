#include "MainWindow.h"

#include <QGraphicsTextItem>
#include <QApplication>
#include <QFont>
#include <QBrush>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
      menuScene(nullptr),
      mainScene(nullptr),
      menus(nullptr) {// Setup view
    
    mainView = new QGraphicsView(this);
    mainView->setRenderHint(QPainter::Antialiasing);
    mainView->setFixedSize(1920, 1080);

    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //mainView->setDragMode(QGraphicsView::NoDrag);

    setCentralWidget(mainView);
    setWindowTitle("Left4Pixels");
    setFixedSize(1920, 1080);


    //StartGame("Lotus", "wave");
    SetupMenuScene();
}

void MainWindow::SetupMenuScene() {
    if (menuScene)
        delete menuScene;

    menuScene = new QGraphicsScene(0, 0, 1000, 1000, this);
    menus = new Menus(menuScene, this);

    mainView->setScene(menuScene);
    menus->AjouterMainWindow(this);
    menus->AfficherMenuPrincipal();
}

 void MainWindow::StartGame(QString map, QString mode, QString mainWeapon) {
    if (mainScene)
        delete mainScene;

    QVector<Entity*> toPreLoad;

    mainScene = new Scene(this);
    mainScene->setSceneRect(0, 0, 20000, 20000);
    mainScene->SetMapName(map);
    mainScene->SetMode(mode);
    Player* player = new Player(nullptr,QStringLiteral("../Resources/Textures/Characters/Player/player.png"),"player",1.0,mainScene,false);
    mainScene->player = player;

    Weapon* primary = new Weapon(player,QStringLiteral("../Resources/Textures/Weapons/Hands/%1.png").arg(mainWeapon),"weapon", mainScene, 10, false);
    Weapon* secondary = new Weapon(player,QStringLiteral("../Resources/Textures/Weapons/Hands/deagle.png"),"weapon", mainScene, 10, false);
    Weapon* melee = new Weapon(player,QStringLiteral("../Resources/Textures/Weapons/Hands/knife.png"),"melee", mainScene, 10, false);

    Entity* outfit = new Entity(player,QStringLiteral("../Resources/Textures/Cosmetics/Player/sunglasses.png"),"cosmetic", mainScene);

    //Here add things you want to have for debug purposes that are entity related, remember to set their Id, attach them to the parent and preload them in the scene.




    //END

    (*player).SetId(QStringLiteral("Cube"));
    (*outfit).SetId(QStringLiteral("sunglasses"));

    player->SetWeapon(primary,0,mainWeapon);
    player->SetWeapon(secondary,1,"deagle");

    player->SetWeapon(melee,2,"knife");
    melee->setVisible(false); //For some reason
    mainScene->meleeCooldown = 0; //we set the melee at 0 since we can melee right when we are in
    mainScene->baseMeleeCooldown = melee->GetReloadTime();


    player->SetCloth(outfit);

    toPreLoad.push_back(player);
    toPreLoad.push_back(primary);
    toPreLoad.push_back(secondary);
    toPreLoad.push_back(melee);

    toPreLoad.push_back(outfit);

    MapLoader* mapLoader = new MapLoader(map, *mainScene);

    for(Entity* entity : toPreLoad) {
        mainScene->AddEntity(entity);
    }

    mainScene->SpawnEnemies("turret", 1, QPointF(3 * 256, 3 * 256), QPointF(256, 256), false);

    secondary->setVisible(false);

    mainView->scale(0.6,0.6);
    mainView->setScene(mainScene);
    return ;
}


void MainWindow::LoadGame() {
    if (mainScene)
        delete mainScene;

    Scene* scene = LoadSave();

    mainScene = scene;

    mainScene->setSceneRect(0, 0, 20000, 20000);

    QVector<Entity*> toPreLoad;


    toPreLoad.push_back(scene->player);
    for (int i = 0; i < 3; ++i) {
        if (scene->player->GetWeapon(i) != nullptr) {
            toPreLoad.push_back(scene->player->GetWeapon(i));
        }
    }
    toPreLoad.push_back(scene->player->GetCloth());

    for(Entity* entity : toPreLoad) {
        mainScene->AddEntity(entity);
    }


    if (scene->player->GetWeapon(1) != nullptr){
        scene->player->GetWeapon(1)->setVisible(false);
    }
    if (scene->player->GetWeapon(2) != nullptr){
        scene->player->GetWeapon(2)->setVisible(false);
    }

    scene->player->setPos(scene->player->pos().x(), scene->player->pos().y());

    scene->currentEnemyCount = 0; // Reset enemy count, since we load a save and enemies are not saved


    mainView->scale(0.5,0.5);
    mainView->setScene(mainScene);

    scene->update();
}




MainWindow::~MainWindow() {
    delete mainScene;
    delete menuScene;
}
