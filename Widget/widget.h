#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>


/*
    A Widget element is an element in the scene

*/

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // WIDGET_H
