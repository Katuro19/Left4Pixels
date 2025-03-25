#include "widget.h"
#include <QKeyEvent>
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent), player(50, 50, 50, 50)
{
    setFixedSize(400, 400);
}

Widget::~Widget() {}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            movePlayer(0, -5);
            break;
        case Qt::Key_Down:
            movePlayer(0, 5);
            break;
        case Qt::Key_Left:
            movePlayer(-5, 0);
            break;
        case Qt::Key_Right:
            movePlayer(5, 0);
            break;
    }
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.drawRect(player);
}

void Widget::movePlayer(int dx, int dy)
{
    player.moveTo(player.x() + dx, player.y() + dy);
}
