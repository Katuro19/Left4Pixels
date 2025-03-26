#include "map.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QElapsedTimer>

Map::Map(Widget *parent) : Widget(parent), bgcolor(Qt::blue)
{
}

void Map::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Dessiner la grille (fond d'écran)
    painter.setPen(QPen(Qt::lightGray)); // Couleur de la grille
    int gridSize = 20; // Taille des cellules de la grille
    for (int x = 0; x < width(); x += gridSize) {
        painter.drawLine(x, 0, x, height()); // Lignes verticales
    }
    for (int y = 0; y < height(); y += gridSize) {
        painter.drawLine(0, y, width(), y); // Lignes horizontales
    }

}
