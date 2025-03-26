#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include "Scene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    Scene* mainScene;
    QGraphicsView* mainView;
    QMenu* helpMenu;


public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_aboutMenu();
};


#endif //MAINWINDOW_H
