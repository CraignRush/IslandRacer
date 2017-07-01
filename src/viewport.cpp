#include "viewport.h"

Viewport::Viewport(int width, int height, Track* track)
{
    //scale(mWidth / 1920.0f * 2.0f,mHeight / 1080.0f * 2.0f);

    // Init variables
    mLapLabel = NULL;
    mTimeLabel = NULL;

    // Set track as scene for this view
    setScene(track);

    // Set size for view and disable scrollbars
    setFixedSize(width, height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Initialize Label for ingame time display
    //mTimeLabel = new QGraphicsTextItem();
    mTimeLabel = new QLabel();
    mTimeLabel->setVisible(false);
    mTimeLabel->setFont(QFont("GillSansMT",24,60)); // Font: family, PointSize, Weight(how bold)
    //mTimeLabel->setDefaultTextColor(QColor("red"));
    mTimeLabel->setStyleSheet("color: red");
    mTimeText = "TIME: ";
    //mTimeLabel->setPlainText(mTimeText + "mm:ss.zzz");
    mTimeLabel->setText(mTimeText + "mm:ss.zzz");
    //Set starting position
    //mTimeLabelPos.setX(width - (mTimeLabel->geometry().width() + 50));
    //mTimeLabelPos.setY(height - (mTimeLabel->geometry().height() + 20));
    //mTimeLabelPos.setX(width - (mTimeLabel->boundingRect().width() + 50));
    //mTimeLabelPos.setY(height - (mTimeLabel->boundingRect().height() + 20));
    //Add it to track
    //track->addItem(mTimeLabel);
    mTimeLabel->setFixedSize(QSize(250,50));
    mTimeLabel->setGeometry(width - mTimeLabel->size().width() - 50, height - mTimeLabel->size().height() - 20, mTimeLabel->size().width(), mTimeLabel->size().height());
    mTimeLabel->setParent(this);

    //Initialize Label for ingame lap counter display
    //mLapLabel = new QGraphicsTextItem();
    mLapLabel = new QLabel();
    mLapLabel->setVisible(false);
    mLapLabel->setFont(QFont("GillSansMT",24,60));
    //mLapLabel->setDefaultTextColor(QColor("red"));
    mLapLabel->setStyleSheet("color: red");
    mLapText = "LAPS: ";
    //mLapLabel->setPlainText(mLapText + "0/3");
    mLapLabel->setText(mLapText + "0/3");
    //Set starting position
    //mLapLabelPos.setX(width - (mLapLabel->geometry().width() + 100));
    //mLapLabelPos.setY(height - (mLapLabel->geometry().height() + 80));
    //track->addItem(mLapLabel);
    mLapLabel->setFixedSize(QSize(250,50));
    mLapLabel->setGeometry(width - mLapLabel->size().width() - 50, height - mLapLabel->size().height() - 80, mLapLabel->size().width(), mLapLabel->size().height());
    mLapLabel->setParent(this);

    connect(track,SIGNAL(LapChanged()),this,SLOT(saveLapTime()));
}

Viewport::~Viewport()
{
    if(mTimeLabel != NULL)
    {
        delete mTimeLabel;
        mTimeLabel = NULL;
    }

    if(mLapLabel != NULL)
    {
        delete mLapLabel;
        mLapLabel = NULL;
    }
}

void Viewport::startGame()
{
    //start the race time immediately after go
    mTimeLabel->setVisible(true);
    mTime.setHMS(0,0,0,0);
    mRaceTime.start();
    mLapLabel->setVisible(true);
}

void Viewport::updateOverlay()
{
    mElapsed = mRaceTime.elapsed();
    mTime.setHMS(0,0,0,0);
    mTime = mTime.addMSecs(mElapsed);
    //mTimeLabel->setHtml(QString("<div style='background:rgba(255, 255, 255, 7%);'>") +mTimeText + mTime.toString("mm:ss.z") + QString("</div>"));
    mTimeLabel->setText(mTimeText + mTime.toString("mm:ss.z"));
    //mTimeLabel->setStyleSheet("color: rgba(255, 255, 255, 7%)");
    //mTimeLabel->setPos(mapToScene(mTimeLabelPos));

    //mLapLabel->setHtml(QString("<div style='background:rgba(255, 255, 255, 7%);'>") + mLapText + QString::number(mLaps) + "/3" + QString("</div>"));
    mLapLabel->setText(mLapText + QString::number(mLaps) + "/3");
    //mLapLabel->setStyleSheet("color: rgba(255, 255, 255, 7%)");
    //mLapLabel->setPlainText(mLapText + QString::number(mLaps) + "/3"); //TODO Optimize the method to get the lap count
    //mLapLabel->setPos(mapToScene(mLapLabelPos));
    /*qDebug() << mElapsed;
    qDebug() << mTime;*/
}

void Viewport::saveLapTime()
{
    mLapTime[mLaps - 1] = mTime.toString("mm:ss.z");
    if(mLaps < 3){
    mLaps++;
    } else {
        // check for highscore
        // if new highscore init Name Dialogue
        // exit_game
    }
    mElapsed = 0;
    mRaceTime.restart();
}
