#include "player.h"
#include "map.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Map map;
    map.show();

    Player player;
    player.show();

    return a.exec();
}
