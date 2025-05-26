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
    void AfficherChoixArme(const QString mode, const QString mapName);


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
    CustomButton* AjouterIcone(const QString imagePath, int x, int y, int width, int height, std::function<void()> callback);
    void ClearCurrentMenu();
    qreal GetViewScale() const;

    enum class MenuType { Main, Pause, Death };
    MenuType currentMenuType = MenuType::Main;
};





#endif // MENUS_H