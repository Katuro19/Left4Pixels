#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new Scene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);
    this->mainView->setBackgroundBrush(QBrush(QColor(200, 200, 200))); 

    this->setCentralWidget(mainView);
    this->setWindowTitle("Left4Pixels");

    mainView->setSceneRect(-600, 0, 500, 500);  // Taille de la scène
    mainView->setFixedSize(800, 600);        // Taille de la fenêtre
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //helpMenu = menuBar()->addMenu(tr("&Help"));
    // QAction* actionHelp = new QAction(tr("&About"), this);
    // connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    // helpMenu->addAction(actionHelp);

}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}


