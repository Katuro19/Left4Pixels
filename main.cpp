#include <QApplication>
#include "MainWindow.h"
#include "Saves.h"
#include <random>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}

