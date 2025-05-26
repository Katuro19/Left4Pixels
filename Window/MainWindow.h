#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "Scene.h"
#include "Menus.h"

class Menus; //Forward declaration

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartGame(QString map, QString mode, QString mainWeapon);
    void LoadGame();
    void SetupMenuScene();


private:
    QGraphicsView *mainView;
    QGraphicsScene *menuScene;
    Scene *mainScene;
    Menus *menus;




};

#endif // MAINWINDOW_H
