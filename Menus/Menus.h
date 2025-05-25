#ifndef MENUS_H
#define MENUS_H

#include "CustomButton.h"
#include "MainWindow.h"
#include <QGraphicsScene>

class MainWindow; // Forward declaration

class Menus {
    public:
        Menus(QGraphicsScene *scene, QObject *parent = nullptr);
        void AfficherMenuPrincipal(std::function<void()> nouvellePartieCallback, std::function<void()> chargerPartieCallback);
        void AfficherMenuPause(const QPointF& centre,std::function<void()> onReprendre,std::function<void()> onSauvegarder, std::function<void()> onQuitter);
        void MasquerMenuPause();
        void AjouterMainWindow(MainWindow* mainWindow);
    private:
        QGraphicsScene *scene;
        QObject *parent;
        QList<QGraphicsItem*> elementsPause;
        QGraphicsRectItem* fondPause = nullptr;
        MainWindow* mainWindow = nullptr;
        //void afficherChoixMap(QString mode);


        void AjouterTitre(const QString &texte);
        void AjouterBouton(const QString &texte, int x, int y, std::function<void()> callback);
};

#endif // MENUS_H