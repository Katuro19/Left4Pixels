#ifndef MENUS_H
#define MENUS_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <functional>

class Menus : public QObject {
    Q_OBJECT
public:
    Menus(QGraphicsScene *scene, QObject *parent = nullptr);

    void afficherMenuPrincipal(std::function<void()> startCallback);
    void afficherMenuPause(std::function<void()> resumeCallback);

private:
    QGraphicsScene *scene;

    void ajouterBouton(const QString &texte, const QPointF &pos, std::function<void()> callback);
};

class BoutonInteractif : public QObject, public QGraphicsRectItem {

public:
    BoutonInteractif(const QString &texte, std::function<void()> callback, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(parent), callback(callback) {

        setRect(0, 0, 200, 50);
        setBrush(QBrush(QColor(70, 70, 70)));
        setPen(QPen(Qt::white));
        setAcceptHoverEvents(true);

        QGraphicsTextItem *label = new QGraphicsTextItem(texte, this);
        QFont font("Arial", 14);
        label->setFont(font);
        label->setDefaultTextColor(Qt::white);
        label->setPos(rect().width() / 2 - label->boundingRect().width() / 2,
                      rect().height() / 2 - label->boundingRect().height() / 2);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        Q_UNUSED(event);
        if (callback) callback();
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override {
        setBrush(QBrush(QColor(100, 100, 100)));
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override {
        setBrush(QBrush(QColor(70, 70, 70)));
    }

private:
    std::function<void()> callback;
};

#endif // MENUS_H
