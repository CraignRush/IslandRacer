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
    mLapTimeText = "LAP TIME: ";
    mLapTimeLabel = new QLabel();
    mLapTimeLabel->setVisible(false);
    mLapTimeLabel->setFont(QFont("GillSansMT",24,60)); // Font: family, PointSize, Weight(how bold)
    mLapTimeLabel->setStyleSheet("color: red");
    mLapTimeLabel->setText(mLapTimeText + "mm:ss.zzz");
    mLapTimeLabel->setFixedSize(QSize(400,50));
    mLapTimeLabel->setGeometry(width - mLapTimeLabel->size().width() - 50, height - mLapTimeLabel->size().height() - 80, mLapTimeLabel->size().width(), mLapTimeLabel->size().height());
    mLapTimeLabel->setParent(this);

    //Initialize Label for ingame total time display
    mTotalTimeText = "TOTAL TIME: ";
    mTotalTimeLabel = new QLabel();
    mTotalTimeLabel->setVisible(false);
    mTotalTimeLabel->setFont(QFont("GillSansMT",24,60)); // Font: family, PointSize, Weight(how bold)
    mTotalTimeLabel->setStyleSheet("color: red");
    mTotalTimeLabel->setText(mTotalTimeText + "mm:ss.zzz");
    mTotalTimeLabel->setFixedSize(QSize(400,50));
    mTotalTimeLabel->setGeometry(width - mTotalTimeLabel->size().width() - 50, height - mTotalTimeLabel->size().height() - 20, mTotalTimeLabel->size().width(), mTotalTimeLabel->size().height());
    mTotalTimeLabel->setParent(this);

    //Initialize Label for ingame lap counter display
    mLapText = "LAPS: ";
    mLapLabel = new QLabel();
    mLapLabel->setVisible(false);
    mLapLabel->setFont(QFont("GillSansMT",24,60));
    mLapLabel->setStyleSheet("color: red");
    mLapLabel->setText(mLapText + "0/3");
    mLapLabel->setFixedSize(QSize(250,50));
    mLapLabel->setGeometry(width - mLapLabel->size().width() - 200, height - mLapLabel->size().height() - 150, mLapLabel->size().width(), mLapLabel->size().height());
    mLapLabel->setParent(this);

    //Initialize Label for speedometer
    mSpeedDisplay = new QLabel();
    mSpeedDisplay->setVisible(false);
    mSpeedDisplay->setStyleSheet("color: red");
    //mSpeedDisplay->setScale(7);
    mSpeedDisplay->setFixedSize(QSize(100,100));
    mSpeedDisplay->setGeometry(10, height - mLapLabel->size().height() - 125, mLapLabel->size().width(), mLapLabel->size().height());
    mSpeedDisplay->setParent(this);
    //mPrevPos = mCar->pos();

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

void Viewport::updateOverlay()
{
    // Update lap time label
    mElapsed = mLapTimeElapsed.elapsed();
    mTime.setHMS(0,0,0,0);
    mTime = mTime.addMSecs(mElapsed);
    mLapTimeLabel->setText(mLapTimeText + mTime.toString("mm:ss.z"));

    //Adjust the total time label position and text
    mElapsed = mTotalTimeElapsed.elapsed();
    mTime2.setHMS(0,0,0,0);
    mTime2 = mTime2.addMSecs(mElapsed);
    mTotalTimeLabel->setText(mTotalTimeText + mTime2.toString("mm:ss.z"));

    // Update laps label
    mLapLabel->setText(mLapText + QString::number(mLaps) + "/3");

    //Display current speed
    //double mSpeed = sqrt(qPow((mCar->x()-mPrevPos.x()),2)+qPow((mCar->y()-mPrevPos.y()),2))/20.f/mFps*1000*3.6*5;
    //mSpeedDisplay->setText("Speed: " + QString::number(mSpeed, 'f', 1) + " km/h");
    //mPrevPos = mCar->pos();
}

void Viewport::saveLapTime()
{
    //mLapTime[mLaps - 1] = mTime.toString("mm:ss.z");
    if(mLaps < 3)
    {
        mLaps++;
    }
    else
    {
        //StopGame();
        mLapTimeEnd[mLaps - 1] = mTime.toString("mm:ss.zzz");
        mTotalTimeEnd = mTime2.toString("mm:ss.zzz");
        //emit RaceFinished(&mLapTimeEnd[3], mTotalTimeEnd);
    }
    mElapsed = 0;
    mLapTimeElapsed.restart();
}

void Viewport::ResumeGame(){
    mLapTimeElapsed.restart();
    mTotalTimeElapsed.restart();
}

