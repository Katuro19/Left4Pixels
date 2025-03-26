#ifndef MAP_H
#define MAP_H


#include "widget.h"
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>

class Map : public Widget
{
    Q_OBJECT

public:
    explicit Map(Widget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor bgcolor;
};

#endif // MAP_H
