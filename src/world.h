#ifndef WORLD_H
#define WORLD_H

#include <QGraphicsView>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QObject>
#include <QKeyEvent>
#include "track.h"
#include "car.h"
#include "player.h"


class World : public QGraphicsView
{
	Q_OBJECT

private:

	int mWidth;                 // Width of world/scene
	int mHeight;                // Height of world/scene
	int level;
	Track* mTrack;
	Car* mCar;
	enum InputState mCurrentInputState;

	b2World* mWorld;             // World object for physic engine

	QTimer* mStartTimer;         // This timer counts the start sequence
	QTimer* mTimer;             // This timer repeatly calls the game loop method
	int mFps;

	int mStartCounter;              // remaining start sequence Time in 10msec steps
	float Opacity;                  // Opacity for fade out effect of StartCounger
	QGraphicsTextItem* mCounter;    // Display Start Counter

    QGraphicsTextItem* mSpeedDisplay;   //Display current Speed
    QPoint mSpeedDisplayPos;
    QPointF mPrevPos;

	QGraphicsTextItem* mLapTimeLabel;		//! contains the String with the elapsed time
	QGraphicsTextItem* mLapLabel;	//! contains the label in the scene
	QGraphicsTextItem* mTotalTimeLabel;
	QPoint mLapLabelPos;
	QPoint mTotalTimeLabelPos;
	QPoint mLapTimeLabelPos;			//! position of the label realtively to the window
	QElapsedTimer mLapTime;		//! computes the elapsed time since "GO!" in ms
	QElapsedTimer mTotalTime;
	QElapsedTimer mPauseTime;		//! Computes the time of pause pressed
	int mElapsed = 0;
	QTime mTime;					//! for translating ms dynamically into mm:ss.zzz
	QTime mTime2;
	QString mLapTimeText;
	QString mTotalTimeText;
	QString mLapText;
	int mLaps = 1;

	void updateOverlay();
	QString mLapTimeEnd[3];
	QString mTotalTimeEnd;
public:
	World(int width,int height);
	//World(int width, int height, int level);
	~World();
	void keyPressEvent(QKeyEvent * keyEvent);
	void keyReleaseEvent(QKeyEvent * keyEvent);
	void loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, QPoint* checkpoint_list, double* angle_list, QPoint carPosition, double carAngle);
	void StopGame();
	void ResumeGame();
	static void GameExit();

public slots:
	void gameLoop();
	void startLoop();
	void saveLapTime();

signals:
	void RaceFinished(QString mLapTime[],QString mTotalTimeEnd);
};

#endif // WORLD_H
