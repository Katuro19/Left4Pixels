#include "Menus.h"

Menus::Menus(QGraphicsScene *scene, QObject *parent)
    : scene(scene), parent(parent) {}

void Menus::AjouterTitre(const QString &texte) {
    QGraphicsTextItem *title = new QGraphicsTextItem(texte);
    QFont font("Arial", 24, QFont::Bold);
    title->setFont(font);
    title->setDefaultTextColor(Qt::white);
    title->setPos(500 - title->boundingRect().width() / 2, 100);
    scene->addItem(title);
}

void Menus::AjouterBouton(const QString &texte, int x, int y, std::function<void()> callback) {
    QGraphicsRectItem *button = new QGraphicsRectItem(0, 0, 200, 50);
    button->setBrush(QBrush(Qt::darkGray));
    button->setPen(QPen(Qt::white));
    button->setPos(x, y);

    // Mettre un Z-index élevé pour le bouton visuel
    button->setZValue(99);

    QGraphicsTextItem *label = new QGraphicsTextItem(texte, button);
    QFont font("Arial", 16);
    label->setFont(font);
    label->setDefaultTextColor(Qt::white);
    label->setPos(100 - label->boundingRect().width() / 2, 10);

    // Créer un bouton cliquable avec un Z-index ENCORE PLUS élevé
    CustomButton *clickable = new CustomButton(callback);
    clickable->setRect(0, 0, 200, 50);
    clickable->setBrush(Qt::NoBrush);
    clickable->setPen(Qt::NoPen);
    clickable->setPos(x, y);

    // Z-index plus élevé que le fond ET que le bouton visuel
    clickable->setZValue(101);

    // S'assurer que le bouton accepte les événements de souris
    clickable->setAcceptedMouseButtons(Qt::LeftButton);

    scene->addItem(button);
    scene->addItem(clickable);

    // Si nous sommes en train de créer des boutons pour le menu pause, ajoutons-les à la liste
    if (!elementsPause.isEmpty()) {
        elementsPause.append(button);
        elementsPause.append(clickable);
    }
}

void Menus::AfficherMenuPrincipal(std::function<void()> nouvellePartieCallback) {
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));
    AjouterTitre("Left4Pixels - Menu Principal");

    /*
    ajouterBouton("Story mode", 400, 250, [this]() {afficherChoixMap("Story");});
    ajouterBouton("Wave mode", 400, 330, [this]() {afficherChoixMap("Wave");});*/
    AjouterBouton("Nouvelle Partie", 400, 250, nouvellePartieCallback);
    AjouterBouton("Quitter", 400, 330, []() {
        qApp->quit();
    });
}

/*
void Menus::afficherChoixMap(QString mode) {
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));
    int y = 200;
    if (mode == "Story"){
        ajouterTitre("Choix de la map - Story mode");
        QStringList maps = { "Map 1", "Map 2", "Map 3" };
        for (const QString& mapName : maps) {
            qDebug() << "1";
            ajouterBouton(mapName, 400, y, [this, mode, mapName]() {mainWindow->StartGame(mapName, mode);});
            qDebug() << "2";
            y += 80;
        }
    }
    if (mode == "Wave"){
        ajouterTitre("Choix de la map - Wave mode");
        QStringList maps = { "Map 1", "Map 2", "Map 3" };
        for (const QString& mapName : maps) {
            ajouterBouton(mapName, 400, y, [this, mode, mapName]() {mainWindow->StartGame(mapName, mode);});

            y += 80;
        }
    }
    ajouterBouton("Retour", 400, y + 40, [this]() {
        afficherMenuPrincipal();
    });
}*/


void Menus::AfficherMenuPause(const QPointF& centre,std::function<void()> onReprendre,std::function<void()> onSauvegarder,std::function<void()> onQuitter) {
    if (!elementsPause.isEmpty()) return;

    // Définir la taille du menu de pause
    int largeurMenu = 2500;
    int hauteurMenu = 2500;

    // Créer un fond centré sur le joueur
    fondPause = new QGraphicsRectItem(
        centre.x() - largeurMenu/2,
        centre.y() - hauteurMenu/2,
        largeurMenu,
        hauteurMenu
    );
    fondPause->setBrush(QColor(0, 0, 0, 200));
    fondPause->setPen(QPen(Qt::white));

    // Z-index plus bas pour le fond
    fondPause->setZValue(98);

    scene->addItem(fondPause);
    elementsPause.append(fondPause);

    QGraphicsTextItem* titre = new QGraphicsTextItem("Pause");
    QFont font("Arial", 24, QFont::Bold);
    titre->setFont(font);
    titre->setDefaultTextColor(Qt::white);
    titre->setPos(centre.x() - titre->boundingRect().width() / 2, centre.y() - hauteurMenu/2 + 20);
    titre->setZValue(99);
    scene->addItem(titre);
    elementsPause.append(titre);

    // Utiliser ajouterBouton pour créer chaque bouton
    AjouterBouton("Reprendre", centre.x() - 100, centre.y() - 80, [this, onReprendre]() {
        qDebug() << "Bouton Reprendre cliqué";
        MasquerMenuPause();
        onReprendre();
    });

    AjouterBouton("Sauvegarder", centre.x() - 100, centre.y() - 10, [this, onSauvegarder]() {
        qDebug() << "Bouton Sauvegarder cliqué";
        onSauvegarder();
    });

    AjouterBouton("Quitter", centre.x() - 100, centre.y() + 60, [this, onQuitter]() {
        qDebug() << "Bouton Quitter cliqué";
        onQuitter();
    });
}

void Menus::MasquerMenuPause() {
    if (elementsPause.isEmpty()) return;
    for (auto* item : elementsPause) {
        if (auto* button = dynamic_cast<CustomButton*>(item)) {
            button->setAcceptedMouseButtons(Qt::NoButton);
        }
    }

    for (auto* item : elementsPause) {
        scene->removeItem(item);
        delete item;
    }

    elementsPause.clear();
    fondPause = nullptr;

    qDebug() << "Menu pause masqué";
}

void Menus::AjouterMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}

