#include "player.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QElapsedTimer>

Player::Player(Widget *parent) : Widget(parent), player(50, 50, 50, 50), dx(0), dy(0), fps(0), frameCount(0)
{
    setFixedSize(400, 400); //Window size

    moveTimer = new QTimer(this); //take player in the timer (for smooth movements)
    connect(moveTimer, &QTimer::timeout, this, &Player::movePlayer);
    moveTimer->start(16);

    timer.start();
    this->show();
}

Player::~Player()
{
    delete moveTimer;
}

void Player::keyPressEvent(QKeyEvent *event)
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

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        dy = 0;
    }
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        dx = 0;
    }
}

void Player::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Dessiner le joueur
    painter.setBrush(Qt::blue);
    painter.drawRect(player);

    // Affichage du FPS
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("FPS: %1").arg(fps));
}

void Player::movePlayer()
{
    player.moveTo(player.x() + dx, player.y() + dy);
    update();  // Redessiner la fenêtre

    // Mettre à jour le FPS à chaque frame
    updateFPS();
}

void Player::updateFPS()
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



