#include "Menus.h"


Menus::Menus(QGraphicsScene *scene, QObject *parent)
    : scene(scene), parent(parent) {
}

Menus::~Menus() {
    ClearCurrentMenu();
    MasquerMenuPause();
}

void Menus::ClearCurrentMenu() {
    for (auto* item : currentMenuItems) {
        scene->removeItem(item);
        delete item;
    }
    currentMenuItems.clear();
}

qreal Menus::GetViewScale() const {
    if (!scene->views().isEmpty()) {
        return scene->views().first()->transform().m11();
    }
    return 1.0;
}

void Menus::AjouterTitre(const QString &texte) {
    auto *title = new QGraphicsTextItem(texte);
    QFont font("Arial", 24, QFont::Bold);
    title->setFont(font);
    title->setDefaultTextColor(Qt::white);
    title->setPos(500 - title->boundingRect().width() / 2, 100);
    title->setZValue(99);
    scene->addItem(title);
    currentMenuItems.append(title);
}

CustomButton* Menus::AjouterBouton(const QString &texte, int x, int y, std::function<void()> callback) {
    qreal scale = GetViewScale();

    // Adjust sizes based on scale
    int largeur = scale < 1.0 ? static_cast<int>(200 / scale) : 200;
    int hauteur = scale < 1.0 ? static_cast<int>(50 / scale) : 50;
    int fontSize = scale < 1.0 ? static_cast<int>(16 / scale) : 16;

    // Create text label (add directly to scene, not as child)
    auto *label = new QGraphicsTextItem(texte);
    QFont font("Arial", fontSize);
    label->setFont(font);
    label->setDefaultTextColor(Qt::white);

    // Position text centered at button location
    label->setPos(x + largeur/2 - label->boundingRect().width() / 2,
                  y + hauteur/2 - label->boundingRect().height() / 2);
    label->setZValue(101); // Higher than clickable area

    // Create clickable area (CustomButton) - this will handle both background and interaction
    auto *clickable = new CustomButton(callback);
    clickable->setRect(0, 0, largeur, hauteur);
    clickable->setPos(x, y);
    clickable->setZValue(100);

    scene->addItem(clickable);
    scene->addItem(label);

    // Track items for cleanup
    if (!elementsPause.isEmpty()) {
        // This is for pause menu
        elementsPause.append(clickable);
        elementsPause.append(label);
    } else {
        // This is for regular menu
        currentMenuItems.append(clickable);
        currentMenuItems.append(label);
    }

    return clickable;
}

void Menus::AfficherMenuPrincipal() {
    ClearCurrentMenu();
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));

    AjouterTitre("Left4Pixels - Menu Principal");

    AjouterBouton("Story mode", 400, 250, [this]() {
        qDebug() << "Story mode button clicked";
        AfficherChoixMap("Story");
    });

    AjouterBouton("Wave mode", 400, 330, [this]() {
        qDebug() << "Wave mode button clicked";
        AfficherChoixMap("Wave");
    });

    AjouterBouton("Charger Partie", 400, 410, [this]() {
        qDebug() << "Load game button clicked";
        if (mainWindow) {
            mainWindow->LoadGame();
        }
    });

    AjouterBouton("Quitter", 400, 490, []() {
        qDebug() << "Quit button clicked";
        qApp->quit();
    });
}

void Menus::AfficherChoixMap(QString mode) {
    ClearCurrentMenu();
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));

    int y = 200;
    QStringList maps = { "Map 1", "Map 2", "Map 3" };

    if (mode == "Story") {
        AjouterTitre("Choix de la map - Story mode");
    } else if (mode == "Wave") {
        AjouterTitre("Choix de la map - Wave mode");
    }

    for (const QString& mapName : maps) {
        AjouterBouton(mapName, 400, y, [this, mode, mapName]() {
            qDebug() << "Map selected:" << mapName << "Mode:" << mode;
            if (mainWindow) {
                mainWindow->StartGame(mapName, mode);
            }
        });
        y += 80;
    }

    AjouterBouton("Retour", 400, y + 40, [this]() {
        qDebug() << "Back button clicked";
        AfficherMenuPrincipal();
    });
}

void Menus::AfficherMenuPause(const QPointF& centre,
                             std::function<void()> onReprendre,
                             std::function<void()> onSauvegarder,
                             std::function<void()> onQuitter) {
    if (!elementsPause.isEmpty()) {
        qDebug() << "Pause menu already displayed";
        return;
    }

    // Define pause menu size
    int largeurMenu = 2500;
    int hauteurMenu = 2500;

    // Create background centered on player
    fondPause = new QGraphicsRectItem(
        centre.x() - largeurMenu/2,
        centre.y() - hauteurMenu/2,
        largeurMenu,
        hauteurMenu
    );
    fondPause->setBrush(QColor(0, 0, 0, 200));
    fondPause->setPen(QPen(Qt::white));
    fondPause->setZValue(97); // Lower than buttons

    scene->addItem(fondPause);
    elementsPause.append(fondPause);

    // Add title
    auto *titre = new QGraphicsTextItem("Pause");
    QFont font("Arial", 24, QFont::Bold);
    titre->setFont(font);
    titre->setDefaultTextColor(Qt::white);
    titre->setPos(centre.x() - titre->boundingRect().width() / 2,
                  centre.y() - hauteurMenu/2 + 20);
    titre->setZValue(99);
    scene->addItem(titre);
    elementsPause.append(titre);

    // Add buttons - note that AjouterBouton will automatically add them to elementsPause
    AjouterBouton("Reprendre", centre.x() - 100, centre.y() - 120, [this, onReprendre]() {
        qDebug() << "Resume button clicked";
        MasquerMenuPause();
        if (onReprendre) onReprendre();
    });

    AjouterBouton("Sauvegarder", centre.x() - 100, centre.y(), [this, onSauvegarder]() {
        qDebug() << "Save button clicked";
        if (onSauvegarder) onSauvegarder();
    });

    AjouterBouton("Quitter", centre.x() - 100, centre.y() + 120, [this, onQuitter]() {
        qDebug() << "Quit button clicked";
        if (onQuitter) onQuitter();
    });

    qDebug() << "Pause menu displayed with" << elementsPause.size() << "elements";
}

void Menus::MasquerMenuPause() {
    if (elementsPause.isEmpty()) {
        qDebug() << "No pause menu to hide";
        return;
    }

    // Clean up all pause menu elements
    for (auto* item : elementsPause) {
        scene->removeItem(item);
        delete item;
    }

    elementsPause.clear();
    fondPause = nullptr;

    qDebug() << "Pause menu hidden";
}

void Menus::AjouterMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}