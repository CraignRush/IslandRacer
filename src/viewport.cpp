#include "viewport.h"

Viewport::Viewport(int width, int height, Track* track)
{
    //scale(mWidth / 1920.0f * 2.0f,mHeight / 1080.0f * 2.0f);
    mWidth = width;
    mHeight = height;
    // Set track as scene for this view
    setScene(track);

    // Set size for view and disable scrollbars
    setFixedSize(mWidth, mHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Initialize Opacity Effect with its clock counter
    mOpacity = 1.0;
    mOpacityEffect = new QGraphicsOpacityEffect(this);
    mOpacityEffect->setOpacity(mOpacity);
    mOpacityTimer = new QTimer();
    mOpacityTimer->setInterval(100);
    connect(mOpacityTimer,SIGNAL(timeout()),this,SLOT(updateLabelOpacity()));



    //Initialize Label for ingame total time display
    mCurToTime = 0;
    mTotalTimeText = "TOTAL TIME: ";
    mTotalTimeLabel = new QLabel();
    mTotalTimeLabel->setVisible(false);
    mTotalTimeLabel->setFont(QFont("GillSansMT",mWidth/80,60)); // Font: family, PointSize, Weight(how bold)
    mTotalTimeLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mTotalTimeLabel->setText(mTotalTimeText + "mm:ss.zzz");
    //    mTotalTimeLabel->setFixedSize(QSize(350,50));
    mTotalTimeLabel->adjustSize();
    mTotalTimeLabel->setParent(this);

    QSize stdRectSize = mTotalTimeLabel->size();
    //Initialize Label for ingame lap counter display
    mLapText = "LAPS: ";
    mLapLabel = new QLabel();
    mLapLabel->setVisible(false);
    mLapLabel->setFont(QFont("GillSansMT",mWidth/80,60));
    mLapLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mLapLabel->setText(mLapText + "0/3");
    mLapLabel->setFixedSize(stdRectSize);
    mLapLabel->setAlignment(Qt::AlignLeft);
    mLapLabel->setParent(this);

    //Initialize Label for ingame time display
    mCurLap = 0;
    mLapTimeText = "LAP TIME: ";
    mLapTimeLabel = new QLabel();
    mLapTimeLabel->setVisible(false);
    mLapTimeLabel->setFont(QFont("GillSansMT",mWidth/80,60)); // Font: family, PointSize, Weight(how bold)
    mLapTimeLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mLapTimeLabel->setText(mLapTimeText + "mm:ss.zzz");
    mLapTimeLabel->setFixedSize(stdRectSize);
    mLapTimeLabel->setAlignment(Qt::AlignLeft);
    mLapTimeLabel->setParent(this);


    //Initialize Label for speedometer
    mSpeedDisplay = new QLabel();
    mSpeedDisplay->setVisible(false);
    mSpeedDisplay->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mSpeedDisplay->setFont(QFont("GillSansMT",mWidth/30,60));
    //    mSpeedDisplay->setFixedSize(QSize(390,110));
    mSpeedDisplay->setText("000.0km/h");
    mSpeedDisplay->adjustSize();
    mSpeedDisplay->setParent(this);
    mPrevPos = QPointF(0,0);

    mLapLabel->setGeometry(mWidth - mLapLabel->size().width() - (0.02 * mWidth), mHeight - (3 * mLapLabel->size().height()) - (3 * (0.2 * mLapLabel->size().height())), mLapLabel->size().width(), mLapLabel->size().height());
    mLapTimeLabel->setGeometry(width - mLapTimeLabel->size().width() - (0.02 * mWidth), mHeight -(2 * mLapTimeLabel->size().height()) - (2 * (0.2 * mLapTimeLabel->size().height())), mLapTimeLabel->size().width(), mLapTimeLabel->size().height());
    mTotalTimeLabel->setGeometry(width - mTotalTimeLabel->size().width() - (0.02 * mWidth), mHeight - mTotalTimeLabel->size().height() - (0.2 * mTotalTimeLabel->size().height()), mTotalTimeLabel->size().width(), mTotalTimeLabel->size().height());
    mSpeedDisplay->setGeometry(0.024 * mHeight, mHeight - mSpeedDisplay->size().height() - (0.024 * mHeight), mSpeedDisplay->size().width(), mSpeedDisplay->size().height());

    mWinnerLabel = NULL;
    mLooserLabel = NULL;

}

Viewport::~Viewport()
{

    delete mOpacityEffect;
    mOpacityEffect = NULL;

    if(mLooserLabel != NULL)
    {
        delete mLooserLabel;
        mLooserLabel = NULL;
    }
    if(mWinnerLabel != NULL)
    {
        delete mWinnerLabel;
        mWinnerLabel = NULL;
    }
  //  if(mOpacityEffect != NULL)
    //{
        //delete mOpacityEffect;
        //mOpacityEffect = NULL;
   // }
   // if(mLapTimeLabel != NULL)
   // {
        delete mLapTimeLabel;
        mLapTimeLabel = NULL;
   // }

  //  if(mLapLabel != NULL)
   // {
        delete mLapLabel;
        mLapLabel = NULL;
   // }

  //  if(mTotalTimeLabel != NULL)
   // {
        delete mTotalTimeLabel;
        mTotalTimeLabel = NULL;
   // }

   // if(mLapTimeLabel != NULL)
    //{
        delete mLapTimeLabel;
        mLapTimeLabel = NULL;
   // }

    //if(mLapLabel != NULL)
    //{
        delete mLapLabel;
        mLapLabel = NULL;
   // }
    //if(mSpeedDisplay != NULL)
    //{
        delete mSpeedDisplay;
        mSpeedDisplay = NULL;
   // }

    delete mOpacityTimer;

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
    double mSpeed = sqrt(qPow((carpos.x()-mPrevPos.x()),2)+qPow((carpos.y()-mPrevPos.y()),2))/20.f*fps*3.6*2.5;
    mSpeedDisplay->setText(QString::number(mSpeed, 'f', 1) + "km/h");
    mPrevPos = carpos;
}

void Viewport::saveLapTime()
{
    //mLapTime[mLaps - 1] = mTime.toString("mm:ss.z");
    if(mLaps >= 2)
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

void Viewport::showLooserLabel()
{
    mLooserLabel = new QLabel;
    mLooserLabel->setVisible(false);
    mLooserLabel->setFont(QFont("GillSansMT",mWidth/20,60));
    mLooserLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,0); color : red; }");
    mLooserLabel->setText("LOOSER!!");
    mLooserLabel->adjustSize();
    mLooserLabel->setGeometry(mWidth/2 - (mLooserLabel->size().width()/2), mHeight/2 - (mLooserLabel->size().height()), mLooserLabel->size().width(), mLooserLabel->size().height());
    // mLooserLabel->setAlignment(Qt::AlignCenter);
    mLooserLabel->setParent(this);
    mLooserLabel->setVisible(true);
    mLooserLabel->setGraphicsEffect(mOpacityEffect);
    mOpacityTimer->start();
}

void Viewport::showWinnerLabel()
{
    mWinnerLabel = new QLabel;
    mWinnerLabel->setVisible(false);
    mWinnerLabel->setFont(QFont("GillSansMT",mWidth/20,60));
    mWinnerLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,0); color : green; }");
    mWinnerLabel->setText("WINNER!!");
    mWinnerLabel->adjustSize();
    mWinnerLabel->setGeometry(mWidth/2 - (mWinnerLabel->size().width()/2), mHeight/2 - (mWinnerLabel->size().height()/2), mWinnerLabel->size().width(), mWinnerLabel->size().height());
    // mWinnerLabel->setAlignment(Qt::AlignCenter);
    mWinnerLabel->setParent(this);
    mWinnerLabel->setVisible(true);
    mWinnerLabel->setGraphicsEffect(mOpacityEffect);
    mOpacityTimer->start();
}

void Viewport::updateLabelOpacity()
{
    if(mOpacity < 0.01){
        mOpacityTimer->stop();

        emit quitGame();
    }
    mOpacity -= 0.025;
    mOpacityEffect->setOpacity(mOpacity);


}



void Viewport::resumeGame()
{
    mLapTimeElapsed.restart();
    mTotalTimeElapsed.restart();
}

void Viewport::pauseGame(bool running)
{
    if(running)
    {
        mCurLap += mLapTimeElapsed.elapsed();
        mCurToTime += mTotalTimeElapsed.elapsed();
    }
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

