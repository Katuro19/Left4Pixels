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
    std::function<void()> StartGame(QString map, QString mode);

private:
    QGraphicsView *mainView;
    QGraphicsScene *menuScene;
    Scene *mainScene;
    Menus *menus;

    void LoadGame(Scene* scene);
    void setupMenuScene();

};

#endif // MAINWINDOW_H
