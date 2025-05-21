#include <QApplication>
#include "MainWindow.h"
#include "Saves.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}

