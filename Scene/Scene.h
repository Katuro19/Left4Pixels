#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QDateTime>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <qcoreapplication.h>
#include <QPropertyAnimation>
#include <QTransform>


#include <vector>
#include <cmath>

#include "Entity.h"
#include "Player.h"
#include "Menus.h"
#include "MapLoader.h"
#include "Projectiles.h"
#include "Enemies.h"
#include "Saves.h"


class Player; //Forward declaration
class Menus; //Forward declaration

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Scene(QObject* parent = nullptr);
    virtual ~Scene();

    Player* player;

    void CameraUpdate(Entity* entity) const;

    void AddEntity(Entity* entity, bool reposition = false, QPointF spawnLocation = QPointF(0,0));
    void DeleteEntity(int index);

    void HandleShooting(QPointF mousePos);

    void SetPlayerPos(QPointF playerPos);

    void SwapIsPaused(){this->isPaused = !this->isPaused;}

    int GetSpawnedEntities() const;
    void SetSpawnedEntities(int newSpawnedEntities);

    bool GetIsPaused() const;
    void SetIsPaused(bool paused);

    void SetPlayer(Player* player);
    Player* GetPlayer() const;

    void SetMapName(QString name) ;
    QString GetMapName();

    void SetMode(QString mode) ;
    QString GetMode();

    int GetScore();
    void AddScore(int moreScore);


    void SetScale(float scaleValue, int durationMs=500);

    void SpawnEnemies(QString type, int number, QPointF position, QPointF spacing, bool verbose = false);

    void togglePause();

    void WaveSpawn();
    QPointF GetSpawnPointAroundPlayer(float distance);

    float spawnTimer = 0;
    int baseSpawnNumber = 1;
    int miniBossSpawn = 50; //At 100 score, first mini boss. Then this will be handled to change !
    int bossSpawn = 150;
    QVector<QString> baseEnemies = {"basic", "runner"};
    QVector<QString> miniBossEnemies = {"spore", "turret"};
    QVector<QString> bossEnemies = {"mother"};

    int currentEnemyCount = 0;
    int maxEnemies = 30;


    //Optimisation :
    QList<Projectile*> projectilePool;
    Projectile* GetProjectileFromPool();


    float meleeCooldown = 0;
    float baseMeleeCooldown = 0;
    int beforeMeleeInt = 0;
    bool hadMelee = false;

public slots:
    void update();



protected:
    QTimer* timer;
    QElapsedTimer frameTimer;


    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    void UpdateDirection() const;
    int totalEntitySpawned = 0;



private:
    QVector<Entity*> Entities; //Will store every entity on the scene
    QSet<int> pressedKeys; //This is used for smooth movements

    void DebugFps();

    bool isPaused = false;
    QVector<QGraphicsItem*> pauseMenuItems;

    Menus* menus = nullptr;

    QString map_name;
    QString mode;

    int score=0; //Kill count
};


#endif //SCENE_H
