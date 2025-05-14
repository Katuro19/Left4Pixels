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

    startGame();
    //setupMenuScene();
}

void MainWindow::setupMenuScene() {
    if (menuScene)
        delete menuScene;

    menuScene = new QGraphicsScene(0, 0, 1000, 1000, this);
    menus = new Menus(menuScene, this);

    mainView->setScene(menuScene);

    menus->afficherMenuPrincipal([this]() {
        startGame();
    });
}

void MainWindow::startGame() {
    if (mainScene)
        delete mainScene;

    mainScene = new Scene(this);
    mainScene->setSceneRect(0, 0, 3000, 3000);
    mainView->scale(0.5,0.5);
    mainView->setScene(mainScene);
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
