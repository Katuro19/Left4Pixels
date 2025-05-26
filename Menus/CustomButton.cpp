#include "CustomButton.h"

CustomButton::CustomButton(std::function<void()> callback) : callback(callback) {
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    // Additional flag that can help with event handling
    setFlag(QGraphicsItem::ItemAcceptsInputMethod, true);

    //qDebug() << "CustomButton created with interactive flags enabled";
}

void CustomButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "CustomButton: mousePressEvent called";

    if (event->button() == Qt::LeftButton) {
        event->accept();
        isPressed = true;
        update();
        //qDebug() << "CustomButton: mousePressEvent - button pressed";
    } else {
        QGraphicsRectItem::mousePressEvent(event);
    }
}

void CustomButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        event->accept();

        if (isPressed && contains(event->pos())) {

            isPressed = false;
            update(); // Update before callback to avoid segfault

            if (callback) {
                callback(); // Execute callback after updating state
            } else {
                qDebug() << "CustomButton: ERROR - callback is null!";
            }
        } else {
            isPressed = false;
            update();
        }
    } else {
        QGraphicsRectItem::mouseReleaseEvent(event);
    }
}

void CustomButton::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();
    //qDebug() << "CustomButton: mouseMoveEvent called";

    // Check if we're still over the button
    bool wasPressed = isPressed;
    if (isPressed && !contains(event->pos())) {
        isPressed = false;
    } else if (wasPressed && !isPressed && contains(event->pos())) {
        isPressed = true;
    }

    if (wasPressed != isPressed) {
        update();
    }
}

void CustomButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    event->accept();
    isHovered = true;
    update();
    //qDebug() << "CustomButton: hover enter";
}

void CustomButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    event->accept();
    isHovered = false;
    isPressed = false; // Reset pressed state when leaving
    update();
    //qDebug() << "CustomButton: hover leave";
}

void CustomButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // Choose color based on state
    QColor currentColor = normalColor;
    if (isPressed) {
        currentColor = pressedColor;
    } else if (isHovered) {
        currentColor = hoverColor;
    }

    // Draw the button
    painter->setBrush(QBrush(currentColor));
    painter->setPen(QPen(Qt::white, 2));
    painter->drawRect(rect());
}
