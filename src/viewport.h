#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsOpacityEffect>
#include <QObject>
#include <QKeyEvent>
#include <QLabel>
#include "track.h"

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

public:
    Viewport(int width, int height, Track* track);
    ~Viewport();
    void startGame();
    void resumeGame();
    void pauseGame(bool running);
    void restartGame();
    //static void GameExit();
    void updateOverlay(QPointF carpos, int fps);

signals:
    void stopGame();
    void quitGame();
    void raceFinished(QString mLapTime[],QString mTotalTimeEnd);

public slots:
    void saveLapTime();
    void showLooserLabel();
    void showWinnerLabel();
    void updateLabelOpacity();

};

#endif // VIEWPORT_H
