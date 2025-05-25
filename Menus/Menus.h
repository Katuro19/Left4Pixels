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
    void AfficherMenuPause(const QPointF& centre,
                          std::function<void()> onReprendre,
                          std::function<void()> onSauvegarder,
                          std::function<void()> onQuitter);
    void MasquerMenuPause();
    void AjouterMainWindow(MainWindow* mainWindow);

private:
    QGraphicsScene *scene;
    QObject *parent;
    QList<QGraphicsItem*> elementsPause;
    QGraphicsRectItem* fondPause = nullptr;
    MainWindow* mainWindow = nullptr;

    // Current menu items for cleanup
    QList<QGraphicsItem*> currentMenuItems;

    void AfficherChoixMap(QString mode);
    void AjouterTitre(const QString &texte);
    CustomButton* AjouterBouton(const QString &texte, int x, int y, std::function<void()> callback);
    void ClearCurrentMenu();
    qreal GetViewScale() const;
};

#endif // MENUS_H