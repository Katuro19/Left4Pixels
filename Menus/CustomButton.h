#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <functional>
#include <QGraphicsTextItem>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>



class CustomButton : public QGraphicsRectItem {
    public:
        CustomButton(std::function<void()> callback);


    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    private:
        std::function<void()> callback;
        bool isPressed = false;
        bool isHovered = false;
};



#endif //CUSTOMBUTTON_H
