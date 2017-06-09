#ifndef WORLD_H
#define WORLD_H

#include <QGraphicsView>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include "track.h"
#include "car.h"

enum InputState
{
    None = 0,
    Accelerate,
    AccelerateSteerRight,
    AccelerateSteerLeft,
    Break,
    BreakSteerRight,
    BreakSteerLeft
};

class World : public QGraphicsView
{
    Q_OBJECT

private:
    int mWidth;                 // Width of world/scene
    int mHeight;                // Height of world/scene

    Track* mTrack;
    Car* mCar;
    enum InputState mCurrentInputState;

    b2World* mWorld;             // World object for physic engine

    QTimer* mTimer;              // This timer repeatly calls the game loop method
    int mLoopIntervalTime;      //

public:
    World(int width, int height);
    void keyPressEvent(QKeyEvent * keyEvent);
    void keyReleaseEvent(QKeyEvent * keyEvent);

public slots:
    void gameLoop();
};

#endif // WORLD_H