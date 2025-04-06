#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>

#include "Scene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    Scene* mainScene;
    QGraphicsView* mainView;


public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();



    
};


#endif //MAINWINDOW_H
