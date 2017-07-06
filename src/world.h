#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include <QTimer>
#include <QObject>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include "track.h"
#include "car.h"
#include "viewport.h"
#include "player.h"
#include "worldposition.h"

class World : public QMainWindow
{
	Q_OBJECT

private:
	int mWidth;                 // Width of world/scene
	int mHeight;                // Height of world/scene

    bool mIsMultiplayer;

    QStackedLayout* mMainLayout;             // Main layout for game window
    QHBoxLayout* mViewportLayout;            // Layout for player viewport side by side
    QHBoxLayout* mCounterLayout;             // Layout for starting countdown
    QWidget* mMainWidget;                    // Main Widget which holds all others and is applied as central widget to main window
    QWidget* mViewportWidget;                // Holds the two viewports
    QWidget* mVerticalSeperatorLine;         // Seperates the two viewports in multiplayer mode
    QWidget* mCounterWidget;                 // Holds label for starting count down
    QWidget* mPauseMenuWidget;
    QGraphicsOpacityEffect* mOpacityEffect;  // Graphics effect to fade out starting count down
    //QGraphicsBlurEffect* mBlurEffect;         // Blur track when pause menu is open

    Car* mCar1;                 // car object (Graphics item) for player 1
    Car* mCar2;                 // car object for player 2

    enum InputState mCurrentInputStatePlayer1;
    enum InputState mCurrentInputStatePlayer2;

    Viewport* mViewPlayer1;     // player's view
    Viewport* mViewPlayer2;     // player's view

    Track* mTrack;              // Graphics scene containing cars
    b2World* mWorld;            // World object for physic engine

    QTimer* mTimer;             // This timer repeatly calls the game loop method
    const int mFps = 25;        // Frames per second (framerate for game loop)

    QTimer* mStartTimer;            // This timer counts the start sequence
    QLabel* mCounter;
    int mStartCounter;              // remaining start sequence Time in 10msec steps
    float mOpacity;                 // Opacity for fade out effect of StartCounter

public:
	World(int width,int height);
    ~World();
    void loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions, int carCount, WorldPosition* carPositions, bool isMultiplayer);
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
    void ResumeGame();
	Viewport *getViewPlayer(int number);

public slots:
	void gameLoop();
	void startLoop();
	void StopGame();
	void ExitGame();
};

#endif // WORLD_H
