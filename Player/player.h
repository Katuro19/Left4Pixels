#ifndef PLAYER_H
#define PLAYER_H


#include "widget.h"
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>

class Player : public Widget
{
    Q_OBJECT

public:
    explicit Player(Widget *parent = nullptr);
    ~Player();


public slots :
    void movePlayer();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


protected :
    void paintEvent(QPaintEvent *event) override;


private:
    QRect player;
    QTimer *moveTimer;
    QElapsedTimer timer;
    int dx, dy;
    int fps;  // Compteur FPS
    int frameCount;  // Compte le nombre de frames
    void updateFPS();
};

#endif // PLAYER_H
