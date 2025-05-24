#include <QApplication>
#include "MainWindow.h"
#include "Saves.h"
#include <random>


int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}

