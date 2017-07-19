#include "world.h"
#include <QDebug>
#include "sound.h"
#include <QThread>
#include <QLabel>
#include <chrono>

using namespace std;
using namespace std::chrono;

World::World(int width, int height) : mWidth{width}, mHeight{height}
{
    // set window title from src.exe to IslandRacer
    setWindowTitle(tr("IslandRacer"));

    // Create Box2D world object (zero gravity)
    mWorld = new b2World(b2Vec2(0.0f, 0.0f));
    mWorld->SetContinuousPhysics(true);

    // Create track
    mTrack = new Track();

    // Create cars
    mCar1 = new Car(mWorld, mTrack);
    mCar2 = new Car(mWorld, mTrack);

    // Connect Car
    connect(this,SIGNAL(setCar1Pixmap(int)),mCar1,SLOT(setCarPixmap(int)));
    connect(this,SIGNAL(setCar2Pixmap(int)),mCar2,SLOT(setCarPixmap(int)));

    // Init viewports
    mViewPlayer1 = NULL;
    mViewPlayer2 = NULL;

    // Disable multiplayer by default
    mIsMultiplayer = false;

    // Init input state
    mCurrentInputStatePlayer1 = None;
    mCurrentInputStatePlayer2 = None;

    // Set up layouts and widgets to display
    mMainWidget = new QWidget(this);
    mViewportWidget = new QWidget(this);
    mVerticalSeperatorLine = new QWidget(this);
    mCounterWidget = new QWidget(this);
    mMainLayout = new QStackedLayout();
    mViewportLayout = new QHBoxLayout(mViewportWidget);
    mCounterLayout = new QHBoxLayout(mCounterWidget);
    mPauseMenuWidget = new PauseMenu(mHeight);
    mOpacityEffect = new QGraphicsOpacityEffect();

    // Init blur effect
    mBlurEffectView1 = NULL;
    mBlurEffectView2 = NULL;

    // Init colorize effect
    mColorize = NULL;

    // Connect start sounds
    connect(this,SIGNAL(playRaceSound1()),Sound::getSoundInstance(this),SLOT(playRaceStart1Sound()));
    connect(this,SIGNAL(playRaceSound2()),Sound::getSoundInstance(this),SLOT(playRaceStart2Sound()));


    // Create horizontal border line between the two viewports
    mVerticalSeperatorLine->setFixedWidth(2);
    mVerticalSeperatorLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mVerticalSeperatorLine->setStyleSheet(QString("background-color: black;"));

    // Set up starting countdown
    mOpacityEffect->setOpacity(1.0);
    mCounter = new QLabel();
    QFont font;
    font.setPointSize(120);
    font.setBold(true);
    mCounter->setStyleSheet("color: rgb(255, 0, 0)");
    mCounter->setFont(font);
    mCounter->setAlignment(Qt::AlignCenter);
    mCounter->setScaledContents(true);
    mCounter->setGraphicsEffect(mOpacityEffect);
    mCounterLayout->addWidget(mCounter, 0, Qt::AlignCenter);

    mCounterWidget->setLayout(mCounterLayout);

    mViewportLayout->setContentsMargins(0,0,0,0);
    mViewportWidget->setLayout(mViewportLayout);
    mViewportWidget->setFocusPolicy(Qt::StrongFocus);

    // hide widget at start and connect signals
    mPauseMenuWidget->setVisible(false);
    connect(mPauseMenuWidget, SIGNAL(resumeGame()), this, SLOT(resumeGame()));
    connect(mPauseMenuWidget, SIGNAL(restartGame()), this, SLOT(restartGame()));
    connect(mPauseMenuWidget, SIGNAL(quitGame()), this, SLOT(exitGame()));

    mMainLayout->setStackingMode(QStackedLayout::StackAll);
    mMainLayout->addWidget(mViewportWidget);
    mMainLayout->addWidget(mCounter);
    mMainLayout->addWidget(mPauseMenuWidget);

    mMainWidget->setLayout(mMainLayout);
    setCentralWidget(mMainWidget);

    //set background properties to pause menu
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(255,255,255,70));
    mPauseMenuWidget->setPalette(pal);
    mPauseMenuWidget->setAutoFillBackground(true);

    // create timer for game loop
    mTimer = new QTimer(this);

    // connect game loop to timer
    connect(mTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));

    // Init objects for start countdown
    mStartTimer = NULL;

    mCarStartingPositions = NULL;
}

World::~World()
{
    // Delete objects from heap and set pointers to NULL
    delete mCar2;
    mCar2 = NULL;

    delete mWorld;
    mWorld = NULL;

    delete mTimer;
    mTimer = NULL;

    delete mTrack;
    mTrack = NULL;

    delete mOpacityEffect;
    mOpacityEffect = NULL;

    delete mCounter;
    mCounter = NULL;

    if(mStartTimer != NULL)
    {
        delete mStartTimer;
        mStartTimer = NULL;
    }

    delete mCounterLayout;
    mCounterLayout = NULL;

    delete mCounterWidget;
    mCounterWidget = NULL;

    if(mBlurEffectView1 != NULL)
    {
        delete mBlurEffectView1;
        mBlurEffectView1 = NULL;
    }

    if(mBlurEffectView2 != NULL)
    {
        delete mBlurEffectView2;
        mBlurEffectView2 = NULL;
    }

    if(mViewPlayer1 != NULL)
    {
        delete mViewPlayer1;
        mViewPlayer1 = NULL;
    }

    if(mViewPlayer2 != NULL)
    {
        delete mViewPlayer2;
        mViewPlayer2 = NULL;
    }

    if(mCarStartingPositions != NULL)
    {
        free(mCarStartingPositions);
        mCarStartingPositions = NULL;
    }

    delete mVerticalSeperatorLine;
    mVerticalSeperatorLine = NULL;

    delete mViewportLayout;
    mViewportLayout = NULL;

    delete mViewportWidget;
    mViewportWidget = NULL;

    delete mPauseMenuWidget;
    mPauseMenuWidget = NULL;

    delete mMainLayout;
    mMainLayout = NULL;

    delete mMainWidget;
    mMainWidget = NULL;
}

void World::gameLoop()
{
    // Compute new positions in physical world
    mWorld->Step(1.0f/mFps, 8, 3);

    // Apply forces dependant on current user input
    mCar1->computeUserInput(mCurrentInputStatePlayer1);
    mCar1->updatePosition(1, mUnderwaterActivePlayer1);
    if(!mUnderwaterActivePlayer1)
        mViewPlayer1->ensureVisible(mCar1, mVisibleWidth, mVisibleHeight);

    // Check for checkpoint collision
    mTrack->updateCheckpoints(mCar1, 1);

    // Render cars on new position
    mCar1->render();

    // Update time/lap overlay
    mViewPlayer1->updateOverlay(mCar1->pos(),mFps);

    // Repeat steps for second car if multiplayer is enabled
    if(mIsMultiplayer)
    {
        mCar2->computeUserInput(mCurrentInputStatePlayer2);
        mCar2->updatePosition(2, mUnderwaterActivePlayer2);
        if(!mUnderwaterActivePlayer2)
            mViewPlayer2->ensureVisible(mCar2,mVisibleWidth, mVisibleHeight);
        mTrack->updateCheckpoints(mCar2, 2);
        mCar2->render();
        mViewPlayer2->updateOverlay(mCar2->pos(),mFps);
    }
}

void World::startLoop()
{
    if(mStartCounter%100==0 && mStartCounter > 0)
    {
        mOpacity=1.0f;
        mCounter->setText(QString::number(mStartCounter/100));
        emit playRaceSound1();
    }
    if(mStartCounter == 0)
    {
        mOpacity=1.0f;
        mCounter->setText("GO!");
        emit playRaceSound2();
        mStartTimer->start(15);

        //start the race time immediately after go
        mViewPlayer1->startGame();
        if(mIsMultiplayer)
            mViewPlayer2->startGame();

        // start game loop and engine sound
        mTimer->start(1000.0/mFps);
        emit mCar1->playCarSound();
    }

    mOpacityEffect->setOpacity(mOpacity);
    mOpacity -= 0.05f;
    mStartCounter -= 5;

    if(mStartCounter == -100)
    {
        mStartTimer->stop();
        delete mStartTimer;
        mStartTimer = NULL;

        mOpacityEffect->setOpacity(0.0);
    }
}

void World::loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions, int carCount, WorldPosition* carPositions, bool isMultiplayer, int speedValue, int accelerationValue, int handlingValue, int carValue)
{
    mIsMultiplayer = isMultiplayer;
    mUnderwaterActivePlayer1 = false;
    mUnderwaterActivePlayer2 = false;

    // copy the starting positions for restart game
    mCarStartingPositions = (WorldPosition*) malloc(20 * sizeof(WorldPosition));
    for(int i = 0; i < carCount; i++)
        mCarStartingPositions[i] = carPositions[i];

    // prepare scene
    mTrack->loadTrack(width, height, QImage(background_path), QImage(gray_path), checkpointCount, checkpointPositions, carResetPositions, mIsMultiplayer);

    // Remove viewports from layout
    if(mViewportLayout->findChild<QWidget*>("mViewPlayer1"))
        mViewportLayout->removeWidget(mViewPlayer1);
    if(mViewportLayout->findChild<QWidget*>("mViewPlayer2"))
        mViewportLayout->removeWidget(mViewPlayer2);

    // Delete existing viewports and blur effects
    if(mBlurEffectView1 != NULL)
    {
        delete mBlurEffectView1;
        mBlurEffectView1 = NULL;
    }

    if(mBlurEffectView2 != NULL)
    {
        delete mBlurEffectView2;
        mBlurEffectView2 = NULL;
    }

    if(mViewPlayer1 != NULL)
    {
        delete mViewPlayer1;
        mViewPlayer1 = NULL;
    }
    if(mViewPlayer2 != NULL)
    {
        delete mViewPlayer2;
        mViewPlayer2 = NULL;
    }

    mPauseMenuWidget->setVisible(false);



    if(mIsMultiplayer)
    {
        srand(time(NULL));
        mCarValue1 = rand() % 7 + 1;
        emit setCar1Pixmap(mCarValue1);
        do{
            srand(time(NULL));
            mCarValue2 = rand() % 7 + 1; // car number from 1 to 7
        }while(mCarValue2 == mCarValue1);
        emit setCar2Pixmap(mCarValue2);

        // Add second car to scene
        mTrack->addItem(mCar1);
        mTrack->addItem(mCar2);

        // set cars to starting position
        mCar1->setPosition(carPositions[0].x(), carPositions[0].y(), carPositions[0].angle());
        mCar2->setPosition(carPositions[1].x(), carPositions[1].y(), carPositions[1].angle());
        mCar1->setCarParams(speedValue, accelerationValue, handlingValue);
        mCar2->setCarParams(speedValue, accelerationValue, handlingValue);

        // Create new Viewports for Player
        mViewPlayer1 = new Viewport(mWidth/2, mHeight, mTrack, true);
        mViewPlayer2 = new Viewport(mWidth/2, mHeight, mTrack, true);

        switch(mCarValue1){
        case 1:
            mViewPlayer1->setLabelStyleSheets(201,0,0,255);
            break;
        case 2:
            mViewPlayer1->setLabelStyleSheets(11,37,196,255);
            break;
        case 3:
            mViewPlayer1->setLabelStyleSheets(0,184,30,255);
            break;
        case 4:
            mViewPlayer1->setLabelStyleSheets(255,234,0,255);
            break;
        case 5:
            mViewPlayer1->setLabelStyleSheets(253,11,244,255);
            break;
        case 6:
            mViewPlayer1->setLabelStyleSheets(254,156,103,255);
            break;
        case 7:
            mViewPlayer1->setLabelStyleSheets(129,129,129,255);
            break;
        }

        switch(mCarValue2){
        case 1:
            mViewPlayer2->setLabelStyleSheets(201,0,0,255);
            break;
        case 2:
            mViewPlayer2->setLabelStyleSheets(11,37,196,255);
            break;
        case 3:
            mViewPlayer2->setLabelStyleSheets(0,184,30,255);
            break;
        case 4:
            mViewPlayer2->setLabelStyleSheets(255,234,0,255);
            break;
        case 5:
            mViewPlayer2->setLabelStyleSheets(253,11,244,255);
            break;
        case 6:
            mViewPlayer2->setLabelStyleSheets(254,156,103,255);
            break;
        case 7:
            mViewPlayer2->setLabelStyleSheets(129,129,129,255);
            break;
        }

        connect(mTrack, SIGNAL(LapChanged1()), mViewPlayer1, SLOT(saveLapTime()));
        connect(mTrack, SIGNAL(LapChanged2()), mViewPlayer2, SLOT(saveLapTime()));

        // Init colorize graphics effect
        mColorize = new QGraphicsColorizeEffect(this);
        mColorStrengthPlayer1 = 0.0;
        mColorStrengthPlayer2 = 0.0;
        mColorize->setStrength(mColorStrengthPlayer1);
        mColorize->setEnabled(false);

        mColorizeTimerPlayer1 = new QTimer(this);
        mColorizeTimerPlayer2 = new QTimer(this);

        connect(mCar1,SIGNAL(startUnderwaterEffect(int)),this,SLOT(startColorizeEffect(int)));
        connect(mCar2,SIGNAL(startUnderwaterEffect(int)),this,SLOT(startColorizeEffect(int)));
        connect(mColorizeTimerPlayer1,SIGNAL(timeout()),this,SLOT(setColorizeStrengthPlayer1()));
        connect(mColorizeTimerPlayer2,SIGNAL(timeout()),this,SLOT(setColorizeStrengthPlayer2()));
        connect(this,SIGNAL(colorize(qreal)),mColorize,SLOT(setStrength(qreal)));
        connect(this,SIGNAL(setCar1Back()),mCar1,SLOT(setToResetPos()));
        connect(this,SIGNAL(setCar2Back()),mCar2,SLOT(setToResetPos()));

        // Set variables for ensureVisible()
        mVisibleWidth = 0.4 * mWidth/2;
        mVisibleHeight =  0.4 * mHeight;

        // Create blur for viewports
        mBlurEffectView1 = new QGraphicsBlurEffect();
        mBlurEffectView2 = new QGraphicsBlurEffect();

        // Blur effect for pause menu
        mBlurEffectView1->setBlurRadius(25.0f);
        mBlurEffectView1->setEnabled(false);
        mBlurEffectView1->setBlurHints(QGraphicsBlurEffect::PerformanceHint);

        mBlurEffectView2->setBlurRadius(25.0f);
        mBlurEffectView2->setEnabled(false);
        mBlurEffectView2->setBlurHints(QGraphicsBlurEffect::PerformanceHint);

        // center cars in view
        mViewPlayer1->centerOn(mCar1);
        mViewPlayer2->centerOn(mCar2);

        // Prevent manually scrolling with arrow keys
        mViewPlayer1->setFocusPolicy(Qt::NoFocus);
        mViewPlayer1->setCacheMode(QGraphicsView::CacheNone);
        mViewPlayer2->setFocusPolicy(Qt::NoFocus);
        mViewPlayer2->setCacheMode(QGraphicsView::CacheNone);

        // Add blur effect
        mViewPlayer1->setGraphicsEffect(mBlurEffectView1);
        mViewPlayer2->setGraphicsEffect(mBlurEffectView2);

        mViewportLayout->addWidget(mViewPlayer2);
        mViewportLayout->addWidget(mVerticalSeperatorLine);
        mViewportLayout->addWidget(mViewPlayer1);

        //connect end race event to stop game loop
        connect(mViewPlayer1, SIGNAL(stopGame()),this, SLOT(stopGame()));
        connect(mViewPlayer2, SIGNAL(stopGame()),this, SLOT(stopGame()));
        connect(mViewPlayer1, SIGNAL(quitGame()),this, SLOT(exitGame()));
        connect(mViewPlayer2, SIGNAL(quitGame()),this, SLOT(exitGame()));
        //Initialize finish sound
        connect(mViewPlayer1,SIGNAL(raceFinished(QString*,QString)),Sound::getSoundInstance(this),SLOT(playFinishSound()));
        connect(mViewPlayer2,SIGNAL(raceFinished(QString*,QString)),Sound::getSoundInstance(this),SLOT(playFinishSound()));
    }
    else
    {
        emit setCar1Pixmap(carValue);
        mTrack->addItem(mCar1);

        // set car to starting position
        mCar1->setPosition(carPositions[0].x(), carPositions[0].y(), carPositions[0].angle());
        mCar1->setCarParams(speedValue, accelerationValue, handlingValue);

        // Create new Viewports for Player
        mViewPlayer1 = new Viewport(mWidth, mHeight, mTrack, true);

        connect(mTrack, SIGNAL(LapChanged1()), mViewPlayer1, SLOT(saveLapTime()));

        // Init colorize graphics effect
        mColorize = new QGraphicsColorizeEffect(this);
        mColorStrengthPlayer1 = 0.0;
        mColorize->setStrength(mColorStrengthPlayer1);
        mColorize->setEnabled(false);

        mColorizeTimerPlayer1 = new QTimer(this);

        connect(mCar1,SIGNAL(startUnderwaterEffect(int)),this,SLOT(startColorizeEffect(int)));
        connect(mColorizeTimerPlayer1,SIGNAL(timeout()),this,SLOT(setColorizeStrengthPlayer1()));
        connect(this,SIGNAL(colorize(qreal)),mColorize,SLOT(setStrength(qreal)));
        connect(this,SIGNAL(setCar1Back()),mCar1,SLOT(setToResetPos()));

        //Initialize finish sound
        connect(mViewPlayer1,SIGNAL(raceFinished(QString*,QString)),Sound::getSoundInstance(this),SLOT(playFinishSound()));

        // Set variables for ensureVisible()
        mVisibleWidth = 0.4 * mWidth;
        mVisibleHeight =  0.4 * mHeight;

        // Create blur for viewport
        mBlurEffectView1 = new QGraphicsBlurEffect();

        //Blur effect for pause menu
        mBlurEffectView1->setBlurRadius(25.0f);
        mBlurEffectView1->setEnabled(false);
        mBlurEffectView1->setBlurHints(QGraphicsBlurEffect::PerformanceHint);

        // Center cars in view
        mViewPlayer1->centerOn(mCar1);

        // Prevent manually scrolling with arrow keys
        mViewPlayer1->setFocusPolicy(Qt::NoFocus);
        mViewPlayer1->setCacheMode(QGraphicsView::CacheBackground);

        mViewPlayer1->setGraphicsEffect(mBlurEffectView1);

        mViewportLayout->addWidget(mViewPlayer1);


        switch(carValue){
        case 1:
            mViewPlayer1->setLabelStyleSheets(201,0,0,255);
            break;
        case 2:
            mViewPlayer1->setLabelStyleSheets(11,37,196,255);
            break;
        case 3:
            mViewPlayer1->setLabelStyleSheets(0,184,30,255);
            break;
        case 4:
            mViewPlayer1->setLabelStyleSheets(255,234,0,255);
            break;
        case 5:
            mViewPlayer1->setLabelStyleSheets(253,11,244,255);
            break;
        case 6:
            mViewPlayer1->setLabelStyleSheets(254,156,103,255);
            break;
        case 7:
            mViewPlayer1->setLabelStyleSheets(129,129,129,255);
            break;
        }

        //connect end race event to stop game loop
        connect(mViewPlayer1, SIGNAL(stopGame()),this, SLOT(stopGame()));
    }

    // Init variables for start countdown
    mOpacity = 1.0f;

    mStartCounter = 390;    // 3.9 sec --> short delay before counter begins
    mCounter->setText(QString(""));

    // Init and start timer for game loop and start loop
    mStartTimer = new QTimer(this);
    connect(mStartTimer, SIGNAL(timeout()), this, SLOT(startLoop()));
    mStartTimer->start(50);
    mCounter->show();


}

void World::startColorizeEffect(int index)
{
    if(index == 1)
    {
        mCar1->setGraphicsEffect(mColorize);
        mUnderwaterActivePlayer1 = true;
        mColorStrengthPlayer1 = 0.0;
        mColorize->setStrength(mColorStrengthPlayer1);
        mColorize->setEnabled(true);
        mColorizeTimerPlayer1->start(100);
    }
    else
    {
        mCar2->setGraphicsEffect(mColorize);
        mUnderwaterActivePlayer2 = true;
        mColorStrengthPlayer2 = 0.0;
        mColorize->setStrength(mColorStrengthPlayer2);
        mColorize->setEnabled(true);
        mColorizeTimerPlayer2->start(100);
    }
}

void World::setColorizeStrengthPlayer1()
{
    if(mColorStrengthPlayer1 < 1.0)
    {
        mColorize->setStrength(mColorStrengthPlayer1);
        mColorStrengthPlayer1 += 0.1;
        mCar1->setScale(mCar1->scale() - 0.067);
        mCar1->setOpacity(mCar1->opacity() - 0.05);
    }
    else if (mColorStrengthPlayer1 < 1.5)
    {
        mColorStrengthPlayer1 += 0.1;
        mCar1->setOpacity(mCar1->opacity() - 0.1);
    }
    else
    {
        mColorize->setEnabled(false);
        mCar1->setScale(1.0f);
        mCar1->setOpacity(1.0f);
        emit setCar1Back();
        mUnderwaterActivePlayer1 = false;
        mColorizeTimerPlayer1->stop();
        mViewPlayer1->centerOn(mCar1);
    }
}

void World::setColorizeStrengthPlayer2()
{
    if(mColorStrengthPlayer2 < 1.0)
    {
        mColorize->setStrength(mColorStrengthPlayer2);
        mColorStrengthPlayer2 += 0.1;
        mCar2->setScale(mCar2->scale() - 0.067);
        mCar2->setOpacity(mCar2->opacity() - 0.05);
    }
    else if (mColorStrengthPlayer2 < 1.5)
    {
        mColorStrengthPlayer2 += 0.1;
        mCar2->setOpacity(mCar2->opacity() - 0.1);
    }
    else
    {
        mColorize->setEnabled(false);
        mCar2->setScale(1.0f);
        mCar2->setOpacity(1.0f);
        emit setCar2Back();
        mUnderwaterActivePlayer2 = false;
        mColorizeTimerPlayer2->stop();
        mViewPlayer2->centerOn(mCar2);
    }
}

void World::keyPressEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        if(mPauseMenuWidget->isVisible()) // resume the game
        {
            resumeGame();
        }
        else // pause the game
        {
            pauseGame();
        }
        break;
    case Qt::Key_Left:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case Accelerate:
            mCurrentInputStatePlayer1 = AccelerateSteerLeft; break;
        case AccelerateSteerRight:
            mCurrentInputStatePlayer1 = Accelerate; break;
        case Break:
            mCurrentInputStatePlayer1 = BreakSteerLeft; break;
        case BreakSteerRight:
            mCurrentInputStatePlayer1 = Break; break;
        case None:
            mCurrentInputStatePlayer1 = SteerLeft; break;
        case SteerRight:
            mCurrentInputStatePlayer1 = None; break;
        }
        break;
    case Qt::Key_Right:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case Accelerate:
            mCurrentInputStatePlayer1 = AccelerateSteerRight; break;
        case AccelerateSteerLeft:
            mCurrentInputStatePlayer1 = Accelerate; break;
        case Break:
            mCurrentInputStatePlayer1 = BreakSteerRight; break;
        case BreakSteerLeft:
            mCurrentInputStatePlayer1 = Break; break;
        case None:
            mCurrentInputStatePlayer1 = SteerRight; break;
        case SteerLeft:
            mCurrentInputStatePlayer1 = None; break;
        }
        break;
    case Qt::Key_Up:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case None:
            mCurrentInputStatePlayer1 = Accelerate; break;
        case SteerLeft:
            mCurrentInputStatePlayer1 = AccelerateSteerLeft; break;
        case SteerRight:
            mCurrentInputStatePlayer1 = AccelerateSteerRight; break;
        case Break:
            mCurrentInputStatePlayer1 = None; break;
        }
        break;
    case Qt::Key_Down:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case None:
            mCurrentInputStatePlayer1 = Break; break;
        case SteerLeft:
            mCurrentInputStatePlayer1 = BreakSteerLeft; break;
        case SteerRight:
            mCurrentInputStatePlayer1 = BreakSteerRight; break;
        case Accelerate:
            mCurrentInputStatePlayer1 = None; break;
        }
        break;
    case Qt::Key_A:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case Accelerate:
            mCurrentInputStatePlayer2 = AccelerateSteerLeft; break;
        case AccelerateSteerRight:
            mCurrentInputStatePlayer2 = Accelerate; break;
        case Break:
            mCurrentInputStatePlayer2 = BreakSteerLeft; break;
        case BreakSteerRight:
            mCurrentInputStatePlayer2 = Break; break;
        case None:
            mCurrentInputStatePlayer2 = SteerLeft; break;
        case SteerRight:
            mCurrentInputStatePlayer2 = None; break;
        }
        break;
    case Qt::Key_D:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case Accelerate:
            mCurrentInputStatePlayer2 = AccelerateSteerRight; break;
        case AccelerateSteerLeft:
            mCurrentInputStatePlayer2 = Accelerate; break;
        case Break:
            mCurrentInputStatePlayer2 = BreakSteerRight; break;
        case BreakSteerLeft:
            mCurrentInputStatePlayer2 = Break; break;
        case None:
            mCurrentInputStatePlayer2 = SteerRight; break;
        case SteerLeft:
            mCurrentInputStatePlayer2 = None; break;
        }
        break;
    case Qt::Key_W:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case None:
            mCurrentInputStatePlayer2 = Accelerate; break;
        case SteerLeft:
            mCurrentInputStatePlayer2 = AccelerateSteerLeft; break;
        case SteerRight:
            mCurrentInputStatePlayer2 = AccelerateSteerRight; break;
        case Break:
            mCurrentInputStatePlayer2 = None; break;
        }
        break;
    case Qt::Key_S:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case None:
            mCurrentInputStatePlayer2 = Break; break;
        case SteerLeft:
            mCurrentInputStatePlayer2 = BreakSteerLeft; break;
        case SteerRight:
            mCurrentInputStatePlayer2 = BreakSteerRight; break;
        case Accelerate:
            mCurrentInputStatePlayer2 = None; break;
        }
        break;
    }
}

void World::keyReleaseEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        break;
    case Qt::Key_Left:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case AccelerateSteerLeft:
            mCurrentInputStatePlayer1 = Accelerate; break;
        case BreakSteerLeft:
            mCurrentInputStatePlayer1 = Break; break;
        case SteerLeft:
            mCurrentInputStatePlayer1 = None; break;
        }
        break;
    case Qt::Key_Right:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case AccelerateSteerRight:
            mCurrentInputStatePlayer1 = Accelerate; break;
        case BreakSteerRight:
            mCurrentInputStatePlayer1 = Break; break;
        case SteerRight:
            mCurrentInputStatePlayer1 = None; break;
        }
        break;
    case Qt::Key_Up:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case Accelerate:
            mCurrentInputStatePlayer1 = None; break;
        case AccelerateSteerLeft:
            mCurrentInputStatePlayer1 = SteerLeft; break;
        case AccelerateSteerRight:
            mCurrentInputStatePlayer1 = SteerRight; break;
        }
        break;
    case Qt::Key_Down:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer1)
        {
        case Break:
            mCurrentInputStatePlayer1 = None; break;
        case BreakSteerLeft:
            mCurrentInputStatePlayer1 = SteerLeft; break;
        case BreakSteerRight:
            mCurrentInputStatePlayer1 = SteerRight; break;
        }
        break;
    case Qt::Key_A:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case AccelerateSteerLeft:
            mCurrentInputStatePlayer2 = Accelerate; break;
        case BreakSteerLeft:
            mCurrentInputStatePlayer2 = Break; break;
        case SteerLeft:
            mCurrentInputStatePlayer2 = None; break;
        }
        break;
    case Qt::Key_D:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case AccelerateSteerRight:
            mCurrentInputStatePlayer2 = Accelerate; break;
        case BreakSteerRight:
            mCurrentInputStatePlayer2 = Break; break;
        case SteerRight:
            mCurrentInputStatePlayer2 = None; break;
        }
        break;
    case Qt::Key_W:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case Accelerate:
            mCurrentInputStatePlayer2 = None; break;
        case AccelerateSteerLeft:
            mCurrentInputStatePlayer2 = SteerLeft; break;
        case AccelerateSteerRight:
            mCurrentInputStatePlayer2 = SteerRight; break;
        }
        break;
    case Qt::Key_S:
        // set new state depending on current state
        switch(mCurrentInputStatePlayer2)
        {
        case Break:
            mCurrentInputStatePlayer2 = None; break;
        case BreakSteerLeft:
            mCurrentInputStatePlayer2 = SteerLeft; break;
        case BreakSteerRight:
            mCurrentInputStatePlayer2 = SteerRight; break;
        }
        break;
    }
}

void World::stopGame()
{
    mTimer->stop();
    emit mCar1->stopCarSound();
}

void World::resumeGame()
{
    // Resume game loop and/or start loop-> physic engine doesn't compute any further step
    if(mStartCounter > 0)
    {
        mStartTimer->start();
        mCounter->show();
    }
    else if(mStartCounter >-100)
    {
        mStartTimer->start();
        mCounter->show();
        mTimer->start();
        // Start race sound
        emit mCar1->playCarSound();
    }
    else
    {
        mTimer->start();
        // Start race sound
        emit mCar1->playCarSound();
    }

    // Stop lap/total timer & hide blur effect
    mViewPlayer1->resumeGame();
    mBlurEffectView1->setEnabled(false);
    if(mIsMultiplayer)
    {
        mViewPlayer2->resumeGame();
        mBlurEffectView2->setEnabled(false);
    }

    // hide pause menu
    mPauseMenuWidget->setVisible(false);
}

void World::restartGame()
{
    // Stop game loop and sound
    mTimer->stop();
    emit mCar1->stopCarSound();

    // Reset car positions & hide blur effect
    mCar1->setPosition(mCarStartingPositions[0]);
    mBlurEffectView1->setEnabled(false);
    mViewPlayer1->centerOn(mCar1);
    mViewPlayer1->restartGame();
    mTrack->ResetCheckpoint(1);

    if(mIsMultiplayer)
    {
        mCar2->setPosition(mCarStartingPositions[1]);
        mBlurEffectView2->setEnabled(false);
        mViewPlayer2->centerOn(mCar2);
        mViewPlayer2->restartGame();
        mTrack->ResetCheckpoint(2);
    }

    // hide pause menu
    mPauseMenuWidget->setVisible(false);

    // Init variables for start countdown
    mOpacity = 1.0f;

    mStartCounter = 390;    // 3.9 sec --> short delay before counter begins
    mCounter->setText(QString(""));
    mCounter->show();

    // Init and start timer for game loop and start loop
    if(mStartTimer != NULL)
    {
        delete mStartTimer;
        mStartTimer = NULL;
    }
    mStartTimer = new QTimer(this);
    connect(mStartTimer, SIGNAL(timeout()), this, SLOT(startLoop()));
    mStartTimer->start(50);
}

void World::pauseGame()
{
    // Pause game loop and/or start loop-> physic engine doesn't compute any further step
    if(mStartCounter > 0)
    {
        mStartTimer->stop();
        mCounter->hide();

        // Pause lap/total timer
        mViewPlayer1->pauseGame(false);
        mBlurEffectView1->setEnabled(true);
        if(mIsMultiplayer)
        {
            mViewPlayer2->pauseGame(false);
            mBlurEffectView2->setEnabled(true);
        }
    }
    else if(mStartCounter >-100)
    {
        mStartTimer->stop();
        mCounter->hide();
        mTimer->stop();

        // Pause lap/total timer
        mViewPlayer1->pauseGame(true);
        mBlurEffectView1->setEnabled(true);
        if(mIsMultiplayer)
        {
            mViewPlayer2->pauseGame(true);
            mBlurEffectView2->setEnabled(true);
        }
    } else {
        mTimer->stop();
        // Pause lap/total timer
        mViewPlayer1->pauseGame(true);
        mBlurEffectView1->setEnabled(true);
        if(mIsMultiplayer)
        {
            mViewPlayer2->pauseGame(true);
            mBlurEffectView2->setEnabled(true);
        }
    }

    // stop race sound
    emit mCar1->stopCarSound();

    // show pause menu
    mPauseMenuWidget->setVisible(true);
}

void World::exitGame()
{
    hide();

    mTimer->stop();
    mTrack->removeItem(mCar1);
    if(mIsMultiplayer){
        mViewportLayout->removeWidget(mVerticalSeperatorLine);
        mTrack->removeItem(mCar2);
    }

    if(mStartTimer != NULL)
    {
        mStartTimer->stop();
        delete mStartTimer;
        mStartTimer = NULL;
    }

    if(mCarStartingPositions != NULL)
    {
        free(mCarStartingPositions);
        mCarStartingPositions = NULL;
    }

    emit mCar1->stopCarSound();

}

Viewport* World::getViewPlayer(int number)
{
    switch (number)
    {
    case 0:
        break;
    case 1:
        return mViewPlayer1;
        break;
    case 2:
        if(mIsMultiplayer)
            return mViewPlayer2;
        break;
    }

    return NULL;
}


