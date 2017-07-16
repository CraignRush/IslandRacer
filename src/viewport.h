#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "underwatereffect.h"
#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsOpacityEffect>
#include <QObject>
#include <QKeyEvent>
#include <QLabel>
#include "track.h"

//! Provides the view for the track
class Viewport : public QGraphicsView
{
    Q_OBJECT

private:
    int mWidth, mHeight;
    QLabel* mSpeedDisplay;              // Display current Speed
    QLabel* mLapTimeLabel;              // contains the String with the elapsed time per lap
    QLabel* mTotalTimeLabel;            // contains the String with the total elapsed time
    QLabel* mLapLabel;                  // contains the label in the scene
    QLabel* mLooserLabel = NULL;
    QLabel* mWinnerLabel = NULL;
    QElapsedTimer mLapTimeElapsed;     	// computes the elapsed time since "GO!" in ms
    QElapsedTimer mTotalTimeElapsed;
    QElapsedTimer mPauseTimeElapsed;	// Computes the time of pause pressed
    int mElapsed = 0;
    QTime mTime;        				// for translating ms dynamically into mm:ss.zzz
    QTime mTime2;
    QString mLapTimeText;
    QString mLapText;
    int mLaps = 1;
    QString mLapTime[3];
    QString mLapTimeEnd[3];
    qint64 mCurLap;

    QString mTotalTimeText;
    QString mTotalTimeEnd;
    qint64 mCurToTime;

    QPointF mPrevPos;

    QGraphicsOpacityEffect* mOpacityEffect;
    double mOpacity;
    QTimer* mOpacityTimer;

    UnderwaterEffect* mUnderwaterEffect;

public:
    //! Generates a QGraphicsView with some display elements
    /*!
     * \param width The width of the view
     * \param height The height of the view
     * \param track The QGraphics scene which is displayed
     */
    Viewport(int width, int height, Track* track);
    ~Viewport();

    //! Init label params for game start
    void startGame();

    //! Restarts the lap and total time counter after pausing game
    void resumeGame();

    //! Save previous time when pausing the game
    /*! If you pause the game during startLoop, running is False and time won't be saved
     * \param running Indicats if pausing the game during gameLoop or starLoop
     */
    void pauseGame(bool running);

    //! Resets all values (e.g. mCurLap or mLaps)to beginnig default
    void restartGame();

    //static void GameExit();
    //! Each time step during gameLoop this function is called to update all labels
    /*! carpos and fps is need to calculate current speed
     * \param carpos Current position of car
     * \param fps Frames per second of the game
     */
    void updateOverlay(QPointF carpos, int fps);

signals:
    //! Signal to the world that all laps are completed and stop game loop
    void stopGame();
    void quitGame();
    //! Signal that race is finished and start end dialog in player class
    void raceFinished(QString mLapTime[],QString mTotalTimeEnd);

public slots:
    //! Slot which is called every time a lap is completed
    /*! Updates all label params for a new lap
     */
    void saveLapTime();
    void showLooserLabel();
    void showWinnerLabel();
    void updateLabelOpacity();

};

#endif // VIEWPORT_H
