#include "Menus.h"


Menus::Menus(QGraphicsScene *scene, QObject *parent)
    : scene(scene), parent(parent) {
}

Menus::~Menus() {
    ClearCurrentMenu();
    MasquerMenuPause();
    MasquerMenuMort();
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

void Menus::AjouterMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
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

    // Create text label
    auto *label = new QGraphicsTextItem(texte);
    QFont font("Arial", fontSize);
    label->setFont(font);
    label->setDefaultTextColor(Qt::white);

    // Position text centered at button location
    label->setPos(x + largeur/2 - label->boundingRect().width() / 2,
                  y + hauteur/2 - label->boundingRect().height() / 2);

    // Create clickable area (CustomButton)
    auto *clickable = new CustomButton(callback);
    clickable->setRect(0, 0, largeur, hauteur);
    clickable->setPos(x, y);

    // Set Z-values based on menu type
    if (currentMenuType == MenuType::Death) {
        clickable->setZValue(101);  // Higher than death menu background (97)
        label->setZValue(102);      // Higher than clickable area
    } else if (currentMenuType == MenuType::Pause) {
        clickable->setZValue(100);
        label->setZValue(101);
    } else {
        clickable->setZValue(100);
        label->setZValue(101);
    }

    scene->addItem(clickable);
    scene->addItem(label);

    // Track items for cleanup based on current menu type
    if (currentMenuType == MenuType::Pause) {
        elementsPause.append(clickable);
        elementsPause.append(label);
    } else if (currentMenuType == MenuType::Death) {
        elementsMort.append(clickable);
        elementsMort.append(label);
    } else {
        currentMenuItems.append(clickable);
        currentMenuItems.append(label);
    }

    //qDebug() << "Button created:" << texte << "for menu type:" << (int)currentMenuType;
    //qDebug() << "Button Z-value:" << clickable->zValue() << "Label Z-value:" << label->zValue();

    return clickable;
}


CustomButton* Menus::AjouterIcone(const QString imagePath, int x, int y, int width, int height, std::function<void()> callback) {
    //qDebug()<<imagePath;
    QPixmap pixmap(imagePath);
    QPixmap scaledPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Image visible
    auto* iconItem = new QGraphicsPixmapItem(scaledPixmap);
    iconItem->setPos(x, y);
    iconItem->setZValue(101); // Visible au-dessus du fond

    // Zone cliquable
    auto* clickable = new CustomButton(callback);
    clickable->setRect(0, 0, width, height);
    clickable->setPos(x, y);
    clickable->setZValue(100); // En-dessous du pixmap

    // Ajout à la scène
    scene->addItem(clickable);
    scene->addItem(iconItem);

    // Suivi pour suppression
    if (currentMenuType == MenuType::Pause)
        elementsPause.append(clickable), elementsPause.append(iconItem);
    else if (currentMenuType == MenuType::Death)
        elementsMort.append(clickable), elementsMort.append(iconItem);
    else
        currentMenuItems.append(clickable), currentMenuItems.append(iconItem);

    return clickable;
}


void Menus::AfficherMenuPrincipal() {
    currentMenuType = MenuType::Main;
    ClearCurrentMenu();
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));

    AjouterTitre("Left4Pixels - Menu Principal");

    AjouterBouton("Story mode", 400, 250, [this]() {
        //qDebug() << "Story mode button clicked";
        AfficherChoixMap("Story");
    });

    AjouterBouton("Wave mode", 400, 330, [this]() {
        //qDebug() << "Wave mode button clicked";
        AfficherChoixMap("Wave");
    });

    AjouterBouton("Charger Partie", 400, 410, [this]() {
        //qDebug() << "Load game button clicked";
        if (mainWindow) {
            mainWindow->LoadGame();
        }
    });

    AjouterBouton("Quitter", 400, 490, []() {
        //qDebug() << "Quit button clicked";
        qApp->quit();
    });
}

void Menus::AfficherChoixMap(QString mode) {
    ClearCurrentMenu();
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));

    int y = 200;
    QStringList maps = { "Lotus", "Pearl", "Debug" };

    if (mode == "Story") {
        AjouterTitre("Choix de la map - Story mode");
    } else if (mode == "Wave") {
        AjouterTitre("Choix de la map - Wave mode");
    }

    for (const QString& mapName : maps) {
        AjouterBouton(mapName, 400, y, [this, mode, mapName]() {
            //qDebug() << "Map selected:" << mapName << "Mode:" << mode;
            AfficherChoixArme(mode, mapName);
        });
        y += 80;
    }

    AjouterBouton("Retour", 400, y + 40, [this]() {
        //qDebug() << "Back button clicked";
        AfficherMenuPrincipal();
    });
}

void Menus::AfficherMenuPause(const QPointF& centre,std::function<void()> onReprendre,std::function<void()> onSauvegarder) {
    if (!elementsPause.isEmpty()) {
        //qDebug() << "Pause menu already displayed";
        return;
    }
    currentMenuType = MenuType::Pause;

    // Define pause menu size
    int largeurMenu = 8000;
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
        //qDebug() << "Resume button clicked";
        MasquerMenuPause();
        if (onReprendre) onReprendre();
    });

    AjouterBouton("Sauvegarder", centre.x() - 100, centre.y(), [this, onSauvegarder]() {
        //qDebug() << "Save button clicked";
        if (onSauvegarder) onSauvegarder();
    });

    AjouterBouton("Quitter", centre.x() - 100, centre.y() + 120, []() {
        //qDebug() << "Quit button clicked";
        qApp->quit();
    });
}


void Menus::AfficherMenuMort(const QPointF& centre) {
    if (!elementsMort.isEmpty()) {
        return;
    }

    // Set the current menu type BEFORE creating buttons
    currentMenuType = MenuType::Death;

    // Get the scene rect to cover the entire visible area
    QRectF sceneRect = scene->sceneRect();
    if (sceneRect.isEmpty() && !scene->views().isEmpty()) {
        QGraphicsView* view = scene->views().first();
        sceneRect = view->mapToScene(view->viewport()->rect()).boundingRect();
    }

    // Create full-screen dark background
    auto* fondMort = new QGraphicsRectItem(sceneRect);
    fondMort->setBrush(QColor(20, 0, 0, 240));
    fondMort->setPen(Qt::NoPen);
    fondMort->setZValue(97);

    scene->addItem(fondMort);
    elementsMort.append(fondMort);

    // Add "GAME OVER" title
    auto *titre = new QGraphicsTextItem("GAME OVER");
    QFont titleFont("Arial", 48, QFont::Bold);
    titre->setFont(titleFont);
    titre->setDefaultTextColor(Qt::red);
    titre->setPos(centre.x() - titre->boundingRect().width() / 2, centre.y() - 150);
    titre->setZValue(98);
    scene->addItem(titre);
    elementsMort.append(titre);

    // Add subtitle
    auto *subtitle = new QGraphicsTextItem("You have been defeated...");
    QFont subtitleFont("Arial", 20);
    subtitle->setFont(subtitleFont);
    subtitle->setDefaultTextColor(Qt::white);
    subtitle->setPos(centre.x() - subtitle->boundingRect().width() / 2, centre.y() - 80);
    subtitle->setZValue(98);
    scene->addItem(subtitle);
    elementsMort.append(subtitle);

    qDebug() << "Creating death menu buttons...";

    // Add "Menu Principal" button
    AjouterBouton("Menu Principal", centre.x() - 200, centre.y(), [this]() {
        qDebug() << "Going back to main menu";
        MasquerMenuMort();
        currentMenuType = MenuType::Main; // Reset menu type
        if (mainWindow) {
            mainWindow->SetupMenuScene();
        }
    });

    // Add "Quitter" button
    AjouterBouton("Quitter", centre.x() - 200, centre.y() + 140, []() {
        qDebug() << "Quit button clicked";
        qApp->quit();
    });

}

void Menus::AfficherChoixArme(const QString mode, const QString mapName) {
    ClearCurrentMenu();
    scene->clear();
    scene->setBackgroundBrush(QColor(30, 30, 30));
    AjouterTitre("Choix de l'arme");

    AjouterIcone(QString("../Resources/Textures/Weapons/Icons/M249.png"), 400, 250, 100, 100, [this, mode, mapName]() {
        if (mainWindow)
            mainWindow->StartGame(mapName, mode, "M249");
    });

    AjouterIcone(QString("../Resources/Textures/Weapons/Icons/M1918.png"), 600, 250, 100, 100, [this, mode, mapName]() {
        if (mainWindow)
            mainWindow->StartGame(mapName, mode, "M1918");
    });

    AjouterBouton("Retour", 400, - 240, [this]() {
        //qDebug() << "Back button clicked";
        AfficherMenuPrincipal();
    });
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

void Menus::MasquerMenuMort() {
    if (elementsMort.isEmpty()) {
        qDebug() << "No death menu to hide";
        return;
    }

    qDebug() << "Hiding death menu with" << elementsMort.size() << "elements";

    // Clean up all death menu elements
    for (auto* item : elementsMort) {
        scene->removeItem(item);
        delete item;
    }

    elementsMort.clear();
    currentMenuType = MenuType::Main; // Reset to main menu type

    qDebug() << "Death menu hidden";
}

