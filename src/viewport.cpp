#include "viewport.h"

Viewport::Viewport(int width, int height, Track* track)
{
	//scale(mWidth / 1920.0f * 2.0f,mHeight / 1080.0f * 2.0f);

	// Set track as scene for this view
	setScene(track);

	// Set size for view and disable scrollbars
	setFixedSize(width, height);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//Initialize Label for ingame time display
    mCurLap = 0;
	mLapTimeText = "LAP TIME: ";
	mLapTimeLabel = new QLabel();
	mLapTimeLabel->setVisible(false);
	mLapTimeLabel->setFont(QFont("GillSansMT",width/100,60)); // Font: family, PointSize, Weight(how bold)
	mLapTimeLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
	mLapTimeLabel->setText(mLapTimeText + "mm:ss.zzz");
	//    mLapTimeLabel->setFixedSize(QSize(300,50));
	mLapTimeLabel->adjustSize();
	mLapTimeLabel->setGeometry(width - mLapTimeLabel->size().width() - 80, height - mLapTimeLabel->size().height() - 80, mLapTimeLabel->size().width(), mLapTimeLabel->size().height());
	mLapTimeLabel->setParent(this);

	//Initialize Label for ingame total time display
    mCurToTime = 0;
	mTotalTimeText = "TOTAL TIME: ";
	mTotalTimeLabel = new QLabel();
	mTotalTimeLabel->setVisible(false);
	mTotalTimeLabel->setFont(QFont("GillSansMT",width/100,60)); // Font: family, PointSize, Weight(how bold)
	mTotalTimeLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
	mTotalTimeLabel->setText(mTotalTimeText + "mm:ss.zzz");
	//    mTotalTimeLabel->setFixedSize(QSize(350,50));
	mTotalTimeLabel->adjustSize();
	mTotalTimeLabel->setGeometry(width - mTotalTimeLabel->size().width() - 30, height - mTotalTimeLabel->size().height() - 20, mTotalTimeLabel->size().width(), mTotalTimeLabel->size().height());
	mTotalTimeLabel->setParent(this);

	//Initialize Label for ingame lap counter display
	mLapText = "LAPS: ";
	mLapLabel = new QLabel();
	mLapLabel->setVisible(false);
	mLapLabel->setFont(QFont("GillSansMT",width/100,60));
	mLapLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
	mLapLabel->setText(mLapText + "0/3");
	//   mLapLabel->setFixedSize(QSize(150,50));
	mLapLabel->adjustSize();
	mLapLabel->setGeometry(width - mLapLabel->size().width() - 230, height - mLapLabel->size().height() - 140, mLapLabel->size().width(), mLapLabel->size().height());
	mLapLabel->setParent(this);

	//Initialize Label for speedometer
	mSpeedDisplay = new QLabel();
	mSpeedDisplay->setVisible(false);
	mSpeedDisplay->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
	mSpeedDisplay->setFont(QFont("GillSansMT",width/50,60));
	//    mSpeedDisplay->setFixedSize(QSize(390,110));
	mSpeedDisplay->setText("000.0km/h");
	mSpeedDisplay->adjustSize();
	mSpeedDisplay->setGeometry(35, height - mSpeedDisplay->size().height() - 35, mSpeedDisplay->size().width(), mSpeedDisplay->size().height());
	mSpeedDisplay->setParent(this);
	mPrevPos = QPointF(0,0);

	connect(track,SIGNAL(LapChanged()),this,SLOT(saveLapTime()));
}

Viewport::~Viewport()
{
	if(mLapTimeLabel != NULL)
	{
		delete mLapTimeLabel;
		mLapTimeLabel = NULL;
	}

	if(mLapLabel != NULL)
	{
		delete mLapLabel;
		mLapLabel = NULL;
	}

	if(mTotalTimeLabel != NULL)
	{
		delete mTotalTimeLabel;
		mTotalTimeLabel = NULL;
	}

	if(mLapTimeLabel != NULL)
	{
		delete mLapTimeLabel;
		mLapTimeLabel = NULL;
	}

	if(mLapLabel != NULL)
	{
		delete mLapLabel;
		mLapLabel = NULL;
	}
	if(mSpeedDisplay != NULL)
	{
		delete mSpeedDisplay;
		mSpeedDisplay = NULL;
	}
}

void Viewport::startGame()
{
	// Display lap time
	mLapTimeLabel->setVisible(true);
	mTime.setHMS(0,0,0,0);
    mLapTimeElapsed.start();

	// Display total time
	mTotalTimeLabel->setVisible(true);
	mTime2.setHMS(0,0,0,0);
	mTotalTimeElapsed.start();

	// Display laps
	mLapLabel->setVisible(true);

	// Display speedometer
	mSpeedDisplay->setVisible(true);
}

void Viewport::updateOverlay(QPointF carpos, int fps)
{
	// Update lap time label
    mElapsed = mLapTimeElapsed.elapsed() + mCurLap;
	mTime.setHMS(0,0,0,0);
	mTime = mTime.addMSecs(mElapsed);
	mLapTimeLabel->setText(mLapTimeText + mTime.toString("mm:ss.z"));

	//Adjust the total time label position and text
    mElapsed = mTotalTimeElapsed.elapsed() + mCurToTime;
	mTime2.setHMS(0,0,0,0);
	mTime2 = mTime2.addMSecs(mElapsed);
	mTotalTimeLabel->setText(mTotalTimeText + mTime2.toString("mm:ss.z"));

	// Update laps label
    mLapLabel->setText(mLapText + QString::number(mLaps) + "/3");

	//Display current speed
    double speed = sqrt(qPow((carpos.x()-mPrevPos.x()),2)+qPow((carpos.y()-mPrevPos.y()),2))/20.f*fps*3.6*2.5;
    mSpeedDisplay->setText(QString::number(speed, 'f', 1) + "km/h");
	mPrevPos = carpos;

}

void Viewport::saveLapTime()
{
	//mLapTime[mLaps - 1] = mTime.toString("mm:ss.z");
    if(mLaps <= 2)
	{
		mLaps++;
	}
	else
	{
		emit stopGame();
		mLapTimeEnd[mLaps - 1] = mTime.toString("mm:ss.zzz");
		mTotalTimeEnd = mTime2.toString("mm:ss.zzz");
		emit raceFinished(&mLapTimeEnd[3], mTotalTimeEnd);
	}
	mElapsed = 0;
    mCurLap = 0;
	mLapTimeElapsed.restart();
}

void Viewport::resumeGame()
{
    mLapTimeElapsed.restart();
    mTotalTimeElapsed.restart();
}

void Viewport::pauseGame()
{
    mCurLap += mLapTimeElapsed.elapsed();
    mCurToTime += mTotalTimeElapsed.elapsed();
}

void Viewport::restartGame()
{
    mCurLap = 0;
    mCurToTime = 0;
    mElapsed = 0;
    mLaps = 1;

    // Hide widgets
    mLapTimeLabel->setVisible(false);
    mTotalTimeLabel->setVisible(false);
    mLapLabel->setVisible(false);
    mSpeedDisplay->setVisible(false);

    // Call twice to set speed to 0.0 km/h
    updateOverlay(QPointF(0.0f, 0.0f), 25);
    updateOverlay(QPointF(0.0f, 0.0f), 25);
}

