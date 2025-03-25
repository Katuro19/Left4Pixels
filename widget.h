#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QRect player;
    QTimer *moveTimer;
    QElapsedTimer timer;
    int dx, dy;
    int fps;  // Compteur FPS
    int frameCount;  // Compte le nombre de frames
    void movePlayer();
    void updateFPS();
};

#endif // WIDGET_H
