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
    //QGraphicsTextItem* mTimeLabel;	// contains the String with the elapsed time
    //QGraphicsTextItem* mLapLabel;	// contains the label in the scene
    QLabel* mTimeLabel;	// contains the String with the elapsed time
    QLabel* mLapLabel;	// contains the label in the scene
    QPoint mLapLabelPos;
    QPoint mTimeLabelPos;			// position of the label realtively to the window
    QElapsedTimer mRaceTime;		// computes the elapsed time since "GO!" in ms
    int mElapsed = 0;
    QTime mTime;					// for translating ms dynamically into mm:ss.zzz
    QString mTimeText;
    QString mLapText;
    int mLaps = 1;
    QElapsedTimer mPauseTime;		// Computes the time of pause pressed
    QString mLapTime[3];

public:
    Viewport(int width, int height, Track* track);
    ~Viewport();
    void startGame();
    void updateOverlay();

public slots:
    void saveLapTime();

};

#endif // VIEWPORT_H
