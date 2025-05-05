#include "Menus.h"
#include <QGraphicsSimpleTextItem>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QApplication>


Menus::Menus(QGraphicsScene *scene, QObject *parent)
    : QObject(parent), scene(scene) {}

void Menus::ajouterBouton(const QString &texte, const QPointF &pos, std::function<void()> callback) {
    auto *bouton = new BoutonInteractif(texte, callback);
    bouton->setPos(pos);
    scene->addItem(bouton);
}

void Menus::afficherMenuPrincipal(std::function<void()> startCallback) {
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));

    QGraphicsTextItem *title = new QGraphicsTextItem("Left4Pixels - Menu Principal");
    QFont titleFont("Arial", 24, QFont::Bold);
    title->setFont(titleFont);
    title->setDefaultTextColor(Qt::white);
    title->setPos(500 - title->boundingRect().width() / 2, 100);
    scene->addItem(title);

    ajouterBouton("Nouvelle Partie", QPointF(400, 250), startCallback);
    ajouterBouton("Quitter", QPointF(400, 330), []() {
        qApp->quit();
    });
}

void Menus::afficherMenuPause(std::function<void()> resumeCallback) {
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30, 180)); // léger fond transparent

    QGraphicsTextItem *title = new QGraphicsTextItem("Pause");
    QFont titleFont("Arial", 20, QFont::Bold);
    title->setFont(titleFont);
    title->setDefaultTextColor(Qt::white);
    title->setPos(500 - title->boundingRect().width() / 2, 150);
    scene->addItem(title);

    ajouterBouton("Reprendre", QPointF(400, 250), resumeCallback);
    ajouterBouton("Quitter", QPointF(400, 330), []() {
        qApp->quit();
    });
}
