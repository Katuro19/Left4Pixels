#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "Scene.h"
#include "Menus.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsView *mainView;
    QGraphicsScene *menuScene;
    Scene *mainScene;
    Menus *menus;

    void LoadGame(Scene* scene);
    void setupMenuScene();
    void startGame();
};

#endif // MAINWINDOW_H
