#ifndef MENUS_H
#define MENUS_H

#include "CustomButton.h"
#include "MainWindow.h"
#include <QGraphicsRectItem>
#include <QList>
#include <QPointF>
#include <functional>
#pragma once


class MainWindow; // Forward declaration
class CustomButton;

class Menus {
public:
    Menus(QGraphicsScene *scene, QObject *parent = nullptr);
    ~Menus();

    void AfficherMenuPrincipal();
    void AfficherMenuPause(const QPointF& centre,std::function<void()> onReprendre,std::function<void()> onSauvegarder);
    void MasquerMenuPause();
    void AjouterMainWindow(MainWindow* mainWindow);
    void AfficherMenuMort(const QPointF& centre);
    void MasquerMenuMort();

    MainWindow* GetMainWindow() const {
        return mainWindow;
    }

private:
    QGraphicsScene *scene;
    QObject *parent;
    QList<QGraphicsItem*> elementsPause;
    QGraphicsRectItem* fondPause = nullptr;
    MainWindow* mainWindow = nullptr;

    // Current menu items for cleanup
    QList<QGraphicsItem*> currentMenuItems;
    QList<QGraphicsItem*> elementsMort;

    void AfficherChoixMap(QString mode);
    void AjouterTitre(const QString &texte);
    CustomButton* AjouterBouton(const QString &texte, int x, int y, std::function<void()> callback);
    void ClearCurrentMenu();
    qreal GetViewScale() const;

    enum class MenuType { Main, Pause, Death };
    MenuType currentMenuType = MenuType::Main;
};


class DebugButton : public QGraphicsRectItem {
public:
    DebugButton(std::function<void()> callback, const QString& name)
        : callback(callback), buttonName(name) {
        setAcceptedMouseButtons(Qt::LeftButton);
        setAcceptHoverEvents(true);
        setBrush(Qt::blue);
        setPen(QPen(Qt::white, 2));
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "DebugButton" << buttonName << ":: mousePressEvent";
        event->accept();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "DebugButton" << buttonName << ":: mouseReleaseEvent";
        if (event->button() == Qt::LeftButton && contains(event->pos())) {
            qDebug() << "DebugButton" << buttonName << ":: EXECUTING CALLBACK";
            if (callback) callback();
        }
        event->accept();
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override {
        qDebug() << "DebugButton" << buttonName << ":: hoverEnter";
        setBrush(Qt::cyan);
        event->accept();
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override {
        qDebug() << "DebugButton" << buttonName << ":: hoverLeave";
        setBrush(Qt::blue);
        event->accept();
    }

private:
    std::function<void()> callback;
    QString buttonName;
};


#endif // MENUS_H