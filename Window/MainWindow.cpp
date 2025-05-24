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
    mainView->setFixedSize(1000, 1000);

    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //mainView->setDragMode(QGraphicsView::NoDrag);

    setCentralWidget(mainView);
    setWindowTitle("Left4Pixels");
    setFixedSize(1000, 1000);


    //StartGame("Lotus", "wave");
    setupMenuScene();
}

void MainWindow::setupMenuScene() {
    if (menuScene)
        delete menuScene;

    menuScene = new QGraphicsScene(0, 0, 1000, 1000, this);
    menus = new Menus(menuScene, this);

    mainView->setScene(menuScene);
    menus->AjouterMainWindow(this);
    menus->afficherMenuPrincipal([this]() {StartGame("Lotus", "wave");});
}

std::function<void()> MainWindow::StartGame(QString map, QString mode) {
    if (mainScene)
        delete mainScene;

    QVector<Entity*> toPreLoad;

    mainScene = new Scene(this);
    mainScene->setSceneRect(0, 0, 20000, 20000);
    mainScene->setMapName(map);
    mainScene->setMode(mode);
    Player* player = new Player(nullptr,QStringLiteral("../Resources/Textures/Characters/Player/player.png"),"player",1.0,mainScene,true);
    mainScene->player = player;

    Weapon* primary = new Weapon(player,QStringLiteral("../Resources/Textures/Weapons/Hands/M249.png"),"weapon", mainScene, 10, false);
    Weapon* secondary = new Weapon(player,QStringLiteral("../Resources/Textures/Weapons/Hands/deagle.png"),"weapon", mainScene, 10, false);
    Entity* outfit = new Entity(player,QStringLiteral("../Resources/Textures/Cosmetics/Player/sunglasses.png"),"cosmetic", mainScene);

    (*player).SetId(QStringLiteral("Cube"));
    (*outfit).SetId(QStringLiteral("sunglasses"));

    player->setWeapon(primary,0,"M249");
    player->setWeapon(secondary,1,"deagle");
    player->setCloth(outfit);

    toPreLoad.push_back(player);
    toPreLoad.push_back(primary);
    toPreLoad.push_back(secondary);
    toPreLoad.push_back(outfit);

    MapLoader* mapLoader = new MapLoader("Debug", *mainScene);

    for(Entity* entity : toPreLoad) {
        mainScene->AddEntity(entity);
    }

    secondary->setVisible(false);

    mainView->scale(0.5,0.5);
    mainView->setScene(mainScene);
    return nullptr;
}


void MainWindow::LoadGame(Scene* scene) {
    if (mainScene)
        delete mainScene;
    mainScene = scene;
    mainScene->setSceneRect(-500, -500, 2500, 2500);
    scene->player->setPos(scene->player->pos().x(), scene->player->pos().y());
}




MainWindow::~MainWindow() {
    delete mainScene;
    delete menuScene;
}
