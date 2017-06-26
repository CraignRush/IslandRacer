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

	QTimer*mStartTimer;         // This timer counts the start sequence
	QTimer* mTimer;             // This timer repeatly calls the game loop method
	int mFps;

	int mStartCounter;              // remaining start sequence Time in 10msec steps
	float Opacity;                  // Opacity for fade out effect of StartCounger
	QGraphicsTextItem* mCounter;    // Display Start Counter

	QGraphicsTextItem* mLabel;		//! contains the String with the elapsed time
	QGraphicsTextItem* mRaceLabel;	//! contains the label in the scene
	QPoint mLabelPos;				//! position of the label realtively to the window
	QElapsedTimer mRaceTime;		//! computes the elapsed time since "GO!" in ms
	int mElapsed = 0;
	QTime mTime;					//! for translating ms dynamically into mm:ss.zzz
	QElapsedTimer mPauseTime;		//! Computes the time of pause pressed

	void updateTime();

public:
	World(int,int);
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
