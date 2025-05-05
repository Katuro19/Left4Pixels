#ifndef MENUS_H
#define MENUS_H

#pragma once
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <qcoreapplication.h>
#include <functional>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <functional>

class MenuButton : public QGraphicsRectItem {
public:
    MenuButton(const QString &text, std::function<void()> onClick, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(parent), callback(onClick)
    {
        setRect(0, 0, 200, 50);
        setBrush(QBrush(Qt::darkGray));
        setAcceptHoverEvents(true);

        label = new QGraphicsTextItem(text, this);
        QFont font("Arial", 14);
        font.setBold(true);
        label->setFont(font);
        label->setDefaultTextColor(Qt::white);
        label->setPos(rect().width() / 2 - label->boundingRect().width() / 2,
                      rect().height() / 2 - label->boundingRect().height() / 2);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (callback) callback();
    }

private:
    QGraphicsTextItem *label;
    std::function<void()> callback;
};

#endif //MENUS_H
