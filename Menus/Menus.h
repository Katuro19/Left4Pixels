#ifndef MENUS_H
#define MENUS_H

#include "CustomButton.h"
#include "MainWindow.h"
#include <QGraphicsScene>

class MainWindow; // Forward declaration

class Menus {
    public:
        Menus(QGraphicsScene *scene, QObject *parent = nullptr);
        void afficherMenuPrincipal(std::function<void()> nouvellePartieCallback);
        void afficherMenuPause(const QPointF& centre,std::function<void()> onReprendre,std::function<void()> onSauvegarder, std::function<void()> onQuitter);
        void masquerMenuPause();
        void AjouterMainWindow(MainWindow* mainWindow);
    private:
        QGraphicsScene *scene;
        QObject *parent;
        QList<QGraphicsItem*> elementsPause;
        QGraphicsRectItem* fondPause = nullptr;
        MainWindow* mainWindow = nullptr;
        //void afficherChoixMap(QString mode);


        void ajouterTitre(const QString &texte);
        void ajouterBouton(const QString &texte, int x, int y, std::function<void()> callback);
};

#endif // MENUS_H