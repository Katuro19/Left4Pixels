#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <functional>
#include <QGraphicsTextItem>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>


#pragma once



class CustomButton : public QGraphicsRectItem {
public:
    CustomButton(std::function<void()> callback);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    std::function<void()> callback;
    bool isPressed = false;
    bool isHovered = false;
    QColor normalColor = Qt::darkGray;
    QColor hoverColor = Qt::gray;
    QColor pressedColor = Qt::lightGray;
};



#endif //CUSTOMBUTTON_H
