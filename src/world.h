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
#include <QGraphicsColorizeEffect>
#include <QGraphicsBlurEffect>
#include <time.h>
#include <cmath>

#include "track.h"
#include "car.h"
#include "viewport.h"
#include "player.h"
#include "worldposition.h"
#include "pausemenu.h"

//! Manage the whole game procedure
class World : public QMainWindow
{
    Q_OBJECT

private:
    int mWidth;                 // Width of world/scene
    int mHeight;                // Height of world/scene

    int mVisibleWidth;          // Widht of rect for ensureVisible()
    int mVisibleHeight;         // Widht of rect for ensureVisible()

    bool mIsMultiplayer;        // Flag if game is in multiplayer mode
    WorldPosition* mCarStartingPositions;   // Starting positions for cars

    QStackedLayout* mMainLayout;             // Main layout for game window
    QHBoxLayout* mViewportLayout;            // Layout for player viewport side by side
    QHBoxLayout* mCounterLayout;             // Layout for starting countdown
    QWidget* mMainWidget;                    // Main Widget which holds all others and is applied as central widget to main window
    QWidget* mViewportWidget;                // Holds the two viewports
    QWidget* mVerticalSeperatorLine;         // Seperates the two viewports in multiplayer mode
    QWidget* mCounterWidget;                 // Holds label for starting count down
    PauseMenu* mPauseMenuWidget;             // Holds the pause menu as a widget
    QGraphicsOpacityEffect* mOpacityEffect;  // Graphics effect to fade out starting count down
    QGraphicsBlurEffect* mBlurEffectView1;   // Blur view1 when pause menu is open
    QGraphicsBlurEffect* mBlurEffectView2;   // Blur view2 when pause menu is open

    Car* mCar1;                 // car object (Graphics item) for player 1
    Car* mCar2;                 // car object for player 2
    int mCarValue1;
    int mCarValue2;

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

    bool mUnderwaterActivePlayer1;      // Flag if swirl animation is active (player1)
    bool mUnderwaterActivePlayer2;      // Flag if swirl animation is active (player2)
    qreal mColorStrengthPlayer1;        // between 0 (transparent) and 1 (fully colorized)
    qreal mColorStrengthPlayer2;        // between 0 (transparent) and 1 (fully colorized)
    QTimer* mColorizeTimerPlayer1;             // timer to enable gradual rendering
    QTimer* mColorizeTimerPlayer2;             // timer to enable gradual rendering
    QGraphicsColorizeEffect* mColorize; // instance of effect

public:
    //! Set up basic game elements
    World(int width,int height);
    ~World();

    //! Load the selected Track and generates all missing elements for the game
    /*!
     * \param width Your screen width
     * \param height Your screen height
     * \param background_path Dir location of the track image
     * \param gray_path Dir location of the grey scale track image
     * \param checkpointCount Number of checkpoints on selected track
     * \param checkpointPositions Array with position of all checkpoints
     * \param carResetPositions Array with position of all reset positions
     * \param carCount Number of Players
     * \param carPositions Car starting position
     * \param isMultiplayer Bool it you selected MP or SP
     * \param speedValue Garage value for topspeed
     * \param accelerationValue Garage value for acceleration
     * \param handlingValue Garage value for handling
     * \param carValue Garage Pixmap for the car
    */
    void loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions, int carCount, WorldPosition* carPositions, bool isMultiplayer, int speedValue, int accelerationValue, int handlingValue, int carValue);

    //! Manage all key press events
    void keyPressEvent(QKeyEvent *keyEvent);

    //! Manage all key release events
    void keyReleaseEvent(QKeyEvent *keyEvent);

    //! Stops game loop to pause the game and display pausemenu
    void pauseGame();

    //! Removes/Sets world elements to load a new track
    static void GameExit();

    //! Get the QGraphicsView of the choosen player
    Viewport *getViewPlayer(int number);

public slots:
    //! Slot for the game loop
    /*! Car movment is calculated and checkpoints are checked
     */
    void gameLoop();

    //! Slot for start loop
    /*! Displays the beginning sequence
     */
    void startLoop();

    //! Resume the game after pause
    void resumeGame();

    //! Restarts the game and sets all values like you just loaded the track
    void restartGame();

    //! Stops game loop after completing all laps
    void stopGame();

    //! End Game
    void exitGame();

    //! Start swirl effect
    //! \param car Car which has water contact
    void startColorizeEffect(int index);

    //! Updates colorize strength player1
    void setColorizeStrengthPlayer1();

    //! Updates colorize strength player1
    void setColorizeStrengthPlayer2();

    //! Determines the winning and loosing label
    void raceFinished(Viewport* viewport);

signals:
    //! Calls the setStrength Slot of the Colorize Effect to change the transparency
    //! \param strength Strength value
    void colorize(qreal strength);

    //! Resets the car1 to last checkpoint
    void setCar1Back();

    //! Resets the car2 to last checkpoint
    void setCar2Back();

    //! Sets the pixmap of the car1
    //! \param i Car index
    void setCar1Pixmap(int i);

    //! Sets the pixmap of the car2
    //! \param i Car index
    void setCar2Pixmap(int i);

    //! Sets the sound effects when a race start (short beep)
    void playRaceSound1();

    //! Sets the sound effects when a race start (long beep)
    void playRaceSound2();

};

#endif // WORLD_H
