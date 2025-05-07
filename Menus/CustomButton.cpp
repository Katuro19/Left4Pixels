#include "CustomButton.h"

CustomButton::CustomButton(std::function<void()> callback) : callback(callback) {
    // S'assurer que le bouton accepte les événements souris
    setAcceptedMouseButtons(Qt::LeftButton);

    // Accepter explicitement le hover pour améliorer la réactivité
    setAcceptHoverEvents(true);
}

void CustomButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "CustomButton: mousePressEvent";
    // Marquer l'événement comme accepté pour empêcher sa propagation à la scène
    event->accept();

    isPressed = true;
    update(); // Déclencher un redessinage
}

// Gérer le relâchement du bouton de la souris
void CustomButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "CustomButton: mouseReleaseEvent";
    // Marquer l'événement comme accepté pour empêcher sa propagation à la scène
    event->accept();

    if (isPressed) {
        isPressed = false;
        // Vérifier que le relâchement se fait bien sur le bouton
        if (contains(event->pos())) {
            qDebug() << "CustomButton: callback exécuté";
            if (callback) callback();
        }
    }
    update(); // Déclencher un redessinage
}

// Gérer quand la souris quitte le bouton pendant un clic
void CustomButton::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // Marquer l'événement comme accepté pour empêcher sa propagation
    event->accept();

    if (isPressed && !contains(event->pos())) {
        isPressed = false;
        update();
    }
}

// Gérer les événements de survol
void CustomButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    isHovered = true;
    update();
}

void CustomButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    isHovered = false;
    update();
}