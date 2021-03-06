#include "viewport.h"


Viewport::Viewport(int width, int height, Track* track, bool isMultiplayer)
{
    mWidth = width;
    mHeight = height;
    // Set track as scene for this view
    setScene(track);
    mIsMultiplayer = isMultiplayer;

    // Set size for view and disable scrollbars
    setFixedSize(mWidth, mHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if(!isMultiplayer){
        mTextSizeSpeed = mWidth/50;
        mTextSizeTime = mWidth/90;
    } else {
        mTextSizeSpeed = mWidth/30;
        mTextSizeTime = mWidth/50;
    }

    //Initialize Opacity Effect with its clock counter
    mOpacity = 1.0;
    mOpacityEffect = new QGraphicsOpacityEffect(this);
    mOpacityEffect->setOpacity(mOpacity);
    mOpacityTimer = new QTimer();
    mOpacityTimer->setInterval(50);
    connect(mOpacityTimer,SIGNAL(timeout()),this,SLOT(updateLabelOpacity()));


    //Initialize Label for ingame total time display
    mCurToTime = 0;
    mTotalTimeText = "TOTAL TIME: ";
    mTotalTimeLabel = new QLabel();
    mTotalTimeLabel->setVisible(false);
    mTotalTimeLabel->setFont(QFont("GillSansMT",mTextSizeTime,60)); // Font: family, PointSize, Weight(how bold)
    mTotalTimeLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mTotalTimeLabel->setText(mTotalTimeText + "mm:ss.zzz");
    mTotalTimeLabel->adjustSize();
    mTotalTimeLabel->setParent(this);

    QSize stdRectSize = mTotalTimeLabel->size();
    mLapText = "LAPS: ";
    mLapLabel = new QLabel();
    mLapLabel->setVisible(false);
    mLapLabel->setFont(QFont("GillSansMT",mTextSizeTime,60));
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
    mLapTimeLabel->setFont(QFont("GillSansMT",mTextSizeTime,60)); // Font: family, PointSize, Weight(how bold)
    mLapTimeLabel->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mLapTimeLabel->setText(mLapTimeText + "mm:ss.zzz");
    mLapTimeLabel->setFixedSize(stdRectSize);
    mLapTimeLabel->setAlignment(Qt::AlignLeft);
    mLapTimeLabel->setParent(this);

    mLapTimeEnd = new QString[3];

    if(isMultiplayer)
        mSpeedDisplay = new Speedometer(0.2 * mHeight,0.2 * mHeight);
    else
        mSpeedDisplay = new Speedometer(0.3 * mHeight,0.3 * mHeight);
    mSpeedDisplay->setVisible(false);
    mSpeedDisplay->adjustSize();
    mSpeedDisplay->setParent(this);
    mPrevPos = QPointF(0,0);

    mLapLabel->setGeometry(mWidth - mLapLabel->size().width() - (0.02 * mWidth), mHeight - (3 * mLapLabel->size().height()) - (3 * (0.2 * mLapLabel->size().height())), mLapLabel->size().width(), mLapLabel->size().height());
    mLapTimeLabel->setGeometry(width - mLapTimeLabel->size().width() - (0.02 * mWidth), mHeight -(2 * mLapTimeLabel->size().height()) - (2 * (0.2 * mLapTimeLabel->size().height())), mLapTimeLabel->size().width(), mLapTimeLabel->size().height());
    mTotalTimeLabel->setGeometry(width - mTotalTimeLabel->size().width() - (0.02 * mWidth), mHeight - mTotalTimeLabel->size().height() - (0.2 * mTotalTimeLabel->size().height()), mTotalTimeLabel->size().width(), mTotalTimeLabel->size().height());
    mSpeedDisplay->setGeometry(0.024 * mHeight, mHeight - mSpeedDisplay->size().height() - (0.024 * mHeight), mSpeedDisplay->size().width(), mSpeedDisplay->size().height());

    mInfoLabel = NULL;
}

Viewport::~Viewport()
{
    delete mOpacityEffect;
    mOpacityEffect = NULL;

    if(mInfoLabel != NULL)
    {
        delete mInfoLabel;
        mInfoLabel = NULL;
    }
    delete mLapTimeLabel;
    mLapTimeLabel = NULL;

    delete mLapLabel;
    mLapLabel = NULL;

    delete mTotalTimeLabel;
    mTotalTimeLabel = NULL;

    delete mLapTimeLabel;
    mLapTimeLabel = NULL;

    delete mLapLabel;
    mLapLabel = NULL;

    delete mSpeedDisplay;
    mSpeedDisplay = NULL;

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
    mSpeedDisplay->setVelocity(mSpeed);
    mPrevPos = carpos;
}

void Viewport::setLabelStyleSheets(int r, int g, int b, int alpha)
{
    QString string("QLabel { background-color : rgba(255,255,255,120); color : rgba(" + QString::number(r) + ","  + QString::number(g) + "," + QString::number(b) + "," + QString::number(alpha) + "); }");
    mTotalTimeLabel->setStyleSheet(string);
    mLapTimeLabel->setStyleSheet(string);
    mLapLabel->setStyleSheet(string);
    mSpeedDisplay->setColor(r,g,b,alpha);
}

void Viewport::saveLapTime()
{
    if(mLaps <= 2) {
        mLapTimeEnd[mLaps - 1] = mTime.toString("mm:ss.z");
        mLaps++;
    }else{
        emit stopGame();
        mLapTimeEnd[mLaps - 1] = mTime.toString("mm:ss.zzz");
        mTotalTimeEnd = mTime2.toString("mm:ss.zzz");
        if(!mIsMultiplayer){
            emit raceFinished(mLapTimeEnd, mTotalTimeEnd);
        } else {
            emit raceFinishedMultiplayer(this);
        }
        mElapsed = 0;
        mCurLap = 0;
        mLapTimeElapsed.restart();
    }
}

void Viewport::showInfoLabel(QString name, int r, int g, int b, int alpha)
{
    mInfoLabel = new QLabel(name);
    mInfoLabel->setVisible(false);
    mInfoLabel->setFont(QFont("GillSansMT",mWidth/20,60));

    QString string("QLabel { background-color : rgba(255,255,255,120); color : rgba(" + QString::number(r) + ","  + QString::number(g) + "," + QString::number(b) + "," + QString::number(alpha) + "); }");
    mInfoLabel->setStyleSheet(string);
    mInfoLabel->adjustSize();
    mInfoLabel->setGeometry(mWidth/2 - (mInfoLabel->size().width()/2), mHeight/2 - (mInfoLabel->size().height()), mInfoLabel->size().width(), mInfoLabel->size().height());
    mInfoLabel->setParent(this);
    mInfoLabel->setVisible(true);
    mInfoLabel->setGraphicsEffect(mOpacityEffect);
    mOpacityTimer->start();
}


void Viewport::updateLabelOpacity()
{
    if(mOpacity < 0.01){
        mOpacityTimer->stop();
        if(mInfoLabel->text() == "Winner!!" || mInfoLabel->text() == "Loooser!!"){
            emit quitGame();
        } else {
            //mInfoLabel->setGraphicsEffect(NULL);
            //mOpacityEffect->setParent(NULL);
            //delete mInfoLabel;
            //mInfoLabel = NULL;
            mInfoLabel->hide();
            mOpacity = 1.0;
        }
    } else {
    mOpacity -= 0.025;
    mOpacityEffect->setOpacity(mOpacity);
    }
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

