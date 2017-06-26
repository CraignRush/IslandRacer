#ifndef WORLD_H
#define WORLD_H

#include <QGraphicsView>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include "track.h"
#include "car.h"




class World : public QGraphicsView
{
    Q_OBJECT

private:
    int mWidth;                 // Width of view
    int mHeight;                // Height of view
    //int level;
    Track* mTrack;
    Car* mCar;
    enum InputState mCurrentInputState;

    b2World* mWorld;            // World object for physic engine

    QTimer* mStartTimer;        // This timer counts the start sequence
    QTimer* mTimer;             // This timer repeatly calls the game loop method
    int mFps;                    // frames per second (default 60)

    int mStartCounter;              // remaining start sequence Time in 10msec steps
    float Opacity;                  // Opacity for fade out effect of StartCounter
    QGraphicsTextItem* mCounter;    // Display Start Counter

public:
    World(int width, int height);
    //World(int width, int height, int level);
    ~World();
    void keyPressEvent(QKeyEvent * keyEvent);
    void keyReleaseEvent(QKeyEvent * keyEvent);
    void loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, QPoint* checkpoint_list, double* angle_list, QPoint carPosition, double carAngle);

public slots:
    void gameLoop();
    void startLoop();
};

#endif // WORLD_H
