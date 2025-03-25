#include "widget.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QElapsedTimer>

Widget::Widget(QWidget *parent) : QWidget(parent), player(50, 50, 50, 50), dx(0), dy(0), fps(0), frameCount(0)
{
    setFixedSize(400, 400);

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Widget::movePlayer);
    moveTimer->start(16);  // Mettre à jour toutes les 16 ms (environ 60 FPS)

    timer.start();
}

Widget::~Widget()
{
    delete moveTimer;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        dy = -5;
    } else if (event->key() == Qt::Key_Down) {
        dy = 5;
    } else if (event->key() == Qt::Key_Left) {
        dx = -5;
    } else if (event->key() == Qt::Key_Right) {
        dx = 5;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        dy = 0;
    }
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        dx = 0;
    }
}

void Widget::paintEvent(QPaintEvent *event)
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

    // Dessiner le joueur
    painter.setBrush(Qt::blue);
    painter.drawRect(player);

    // Affichage du FPS
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("FPS: %1").arg(fps));
}

void Widget::movePlayer()
{
    player.moveTo(player.x() + dx, player.y() + dy);
    update();  // Redessiner la fenêtre

    // Mettre à jour le FPS à chaque frame
    updateFPS();
}

void Widget::updateFPS()
{
    // Calculer le temps écoulé depuis la dernière frame
    qint64 elapsed = timer.elapsed();

    // Si plus de 1 seconde s'est écoulée, on calcule les FPS
    if (elapsed >= 1000) {
        fps = frameCount;  // On met à jour le compteur FPS
        frameCount = 0;    // Réinitialiser le compteur de frames
        timer.restart();   // Redémarrer le timer
    } else {
        frameCount++;
    }
}


