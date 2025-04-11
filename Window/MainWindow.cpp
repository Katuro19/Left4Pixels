#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new Scene;
    this->mainView = new QGraphicsView;

    this->mainView->setScene(mainScene);
    this->mainView->setBackgroundBrush(QBrush(QColor(200, 200, 200))); 

    this->setCentralWidget(mainView);
    this->setWindowTitle("Left4Pixels");

    mainView->setSceneRect(-500, -500, 1000, 1000);  // Taille de la scène
    mainView->setFixedSize(1000, 1000);        // Taille de la fenêtre
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainView->scale(1.0, 1.0);  // Zoom x2





}


MainWindow::~MainWindow(){

}




