#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QTime>
#include <QElapsedTimer>
#include <QObject>
#include <QKeyEvent>
#include <QLabel>
#include "track.h"

class Viewport : public QGraphicsView
{
    Q_OBJECT

private:
    QLabel* mSpeedDisplay;              // Display current Speed
    QLabel* mLapTimeLabel;              // contains the String with the elapsed time per lap
    QLabel* mTotalTimeLabel;            // contains the String with the total elapsed time
    QLabel* mLapLabel;                  // contains the label in the scene
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

public:
    Viewport(int width, int height, Track* track);
    ~Viewport();
    void startGame();
    void ResumeGame();
    void pauseGame();
    //static void GameExit();
    void updateOverlay(QPointF carpos, int fps);

signals:
	 void StopGame();
	void RaceFinished(QString mLapTime[],QString mTotalTimeEnd);
public slots:
    void saveLapTime();

};

#endif // VIEWPORT_H
