#include "world.h"
#include <QDebug>
#include "sound.h"
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

    // Create track
    mTrack = new Track();

    // Create cars
    mCar1 = new Car(mWorld, mTrack, 1);
    mCar2 = new Car(mWorld, mTrack, 2);

    // Add the cars to the track/scene
    //mTrack->addItem(mCar1);
    //mTrack->addItem(mCar2);

    // Init viewports
    mViewPlayer1 = NULL;
    mViewPlayer2 = NULL;

    // Disable multiplayer by default
    mIsMultiplayer = false;

    // Init input state
    mCurrentInputStatePlayer1 = None;
    mCurrentInputStatePlayer2 = None;

    // Set up layouts and widgets to display
    mMainLayout = new QStackedLayout(this);
    mViewportLayout = new QHBoxLayout(this);
    mCounterLayout = new QHBoxLayout(this);
    mMainWidget = new QWidget();
    mViewportWidget = new QWidget();
    mVerticalSeperatorLine = new QWidget();
    mCounterWidget = new QWidget();
    mPauseMenuWidget = new PauseMenu(mHeight);
    mOpacityEffect = new QGraphicsOpacityEffect();

    // Init blur effect
    mBlurEffectView1 = NULL;
    mBlurEffectView2 = NULL;

    // Create horizontal border line between the two viewports
    //line->setFrameShape(QFrame::VLine);
    mVerticalSeperatorLine->setFixedWidth(2);
    mVerticalSeperatorLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //line->setFrameShadow(QFrame::Sunken);
    // set black background of line
    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, Qt::black);
    //line->setAutoFillBackground(true);
    //line->setPalette(pal);
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
    //delete mCar1;
    //mCar1 = NULL;

    delete mCar2;
    mCar2 = NULL;

    delete mWorld;
    mWorld = NULL;

    delete mTimer;
    mTimer = NULL;

    delete mTrack;
    mTrack = NULL;

    //if(mOpacityEffect != NULL)
    // {
    delete mOpacityEffect;
    mOpacityEffect = NULL;
    // }

    //if(mCounter != NULL)
    //{
    delete mCounter;
    mCounter = NULL;
    //}

    if(mStartTimer != NULL)
    {
        delete mStartTimer;
        mStartTimer = NULL;
    }

    delete mCounterLayout;
    mCounterLayout = NULL;

    //if(mCounterWidget != NULL)
    // {
    delete mCounterWidget;
    mCounterWidget = NULL;
    // }

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
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //	QElapsedTimer timer;
    //	timer.start();

    // Compute new positions in physical world
    mWorld->Step(1.0f/mFps, 8, 3);

    // Apply forces dependant on current user input
    mCar1->computeUserInput(mCurrentInputStatePlayer1);
    mCar1->updatePosition(1);
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
        mCar2->updatePosition(2);
        mViewPlayer2->ensureVisible(mCar2,mVisibleWidth, mVisibleHeight);
        mTrack->updateCheckpoints(mCar2, 2);
        mCar2->render();
        mViewPlayer2->updateOverlay(mCar2->pos(),mFps);
    }

    //	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    //	auto duration = duration_cast<microseconds>(t2-t1).count();
    //	qDebug() << duration;

    //	qDebug() << "The slow operation took" << timer.elapsed() << "nanoseconds";
}

void World::startLoop()
{
    if(mStartCounter%100==0 && mStartCounter > 0)
    {
        mOpacity=1.0f;
        //mCounter->setPlainText(QString::number(mStartCounter/100));
        mCounter->setText(QString::number(mStartCounter/100));
        //mCounter->setPos(mapToScene((mWidth - mCounter->boundingRect().width()-20)/2,(mHeight-200)/2));
        //mCounter->setPos((mWidth - mCounter->boundingRect().width()-20)/2,(mHeight-200)/2);
    }
    if(mStartCounter == 0)
    {
        mOpacity=1.0f;
        //mCounter->setPlainText("GO!");
        mCounter->setText("GO!");
        //mCounter->setPos(mapToScene((mWidth - mCounter->boundingRect().width()-60)/2,(mHeight-200)/2));
        //mCounter->setPos((mWidth - mCounter->boundingRect().width()-60)/2,(mHeight-200)/2);
        mStartTimer->start(15);

        //start the race time immediately after go
        mViewPlayer1->startGame();
        if(mIsMultiplayer)
            mViewPlayer2->startGame();

        // start game loop and engine sound
        mTimer->start(1000.0/mFps);
        emit mCar1->playCarSound();
    }

    //mCounter->setOpacity(mOpacity);
    //mCounter->setStyleSheet("color: rgba(255, 0, 0, " + QString::number(mOpacity*100) + "%)");
    mOpacityEffect->setOpacity(mOpacity);
    mOpacity -= 0.05f;
    mStartCounter -= 5;

    if(mStartCounter == -100)
    {
        mStartTimer->stop();
        delete mStartTimer;
        mStartTimer = NULL;

        mOpacityEffect->setOpacity(0.0);
        /*delete mCounterWidget;
        mCounterWidget = NULL;

        delete mOpacityEffect;
        mOpacityEffect = NULL;

        delete mCounter;
        mCounter = NULL;*/
        //mTrack->removeItem(mCounter);
        //delete mCounter;
        //mCounter = NULL;
    }
}

void World::loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions, int carCount, WorldPosition* carPositions, bool isMultiplayer, int speedValue, int accelerationValue, int handlingValue)
{
    mIsMultiplayer = isMultiplayer;

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

        connect(mTrack, SIGNAL(LapChanged1()), mViewPlayer1, SLOT(saveLapTime()));
        connect(mTrack, SIGNAL(LapChanged2()), mViewPlayer2, SLOT(saveLapTime()));

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
    }
    else
    {
        mTrack->addItem(mCar1);

        // set car to starting position
        mCar1->setPosition(carPositions[0].x(), carPositions[0].y(), carPositions[0].angle());
        mCar1->setCarParams(speedValue, accelerationValue, handlingValue);

        // Create new Viewports for Player
        mViewPlayer1 = new Viewport(mWidth, mHeight, mTrack, true);

        connect(mTrack, SIGNAL(LapChanged1()), mViewPlayer1, SLOT(saveLapTime()));

        mVisibleWidth = 0.4 * mWidth;
        mVisibleHeight =  0.4 * mHeight;

        // Create blur for viewport
        mBlurEffectView1 = new QGraphicsBlurEffect();

        // Blur effect for pause menu
        mBlurEffectView1->setBlurRadius(25.0f);
        mBlurEffectView1->setEnabled(false);
        mBlurEffectView1->setBlurHints(QGraphicsBlurEffect::PerformanceHint);

        // center cars in view
        mViewPlayer1->centerOn(mCar1);

        // Prevent manually scrolling with arrow keys
        mViewPlayer1->setFocusPolicy(Qt::NoFocus);
        mViewPlayer1->setCacheMode(QGraphicsView::CacheNone);

        mViewPlayer1->setGraphicsEffect(mBlurEffectView1);

        mViewportLayout->addWidget(mViewPlayer1);

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

void World::keyPressEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
    case Qt::Key_Escape: // Just for debugging, to close game and get back to menu.
        if(mPauseMenuWidget->isVisible()) // resume the game
        {
            resumeGame();
        }
        else // pause the game
        {
            pauseGame();
        }

        //ExitGame();

        /*
 * 		ExitGame();

        hide();
        //mBlurEffect->setEnabled(false);

        mTimer->stop();
        mTrack->removeItem(mCar1);
        if(mIsMultiplayer)
            mTrack->removeItem(mCar2);
        /*if(mCounter != NULL)
        {
            delete mCounter;
            mCounter = NULL;
        }*/
        /*       if(mStartTimer != NULL)
        {
            mStartTimer->stop();
            delete mStartTimer;
            mStartTimer = NULL;
        }

        emit mCar1->stopCarSound();
*/
        //        if(mSpeedDisplay != NULL)
        //        {
        //            delete mSpeedDisplay;
        //            mSpeedDisplay = NULL;
        //        }

        //        if(mTimeLabel != NULL)
        //        {
        //            delete mTimeLabel;
        //            mTimeLabel = NULL;
        //        }
        //        if(mLapLabel != NULL)
        //        {
        //            delete mLapLabel;
        //            mLapLabel = NULL;
        //        }
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
        //mBlurEffect->setEnabled(true);
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

    // focus mViewportWidget to receive key input events
    //mViewportWidget->focusWidget();
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

    // add blur effect (disable viewport updates so blur won't be removed with repaint)
    //mViewPlayer1->setUpdatesEnabled(false);
    //if(mIsMultiplayer)
    //  mViewPlayer2->setUpdatesEnabled(false);

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
    /*if(mCounter != NULL)
    {
        delete mCounter;
        mCounter = NULL;
    }*/
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
    //        if(mSpeedDisplay != NULL)
    //        {
    //            delete mSpeedDisplay;
    //            mSpeedDisplay = NULL;
    //        }

    //        if(mTimeLabel != NULL)
    //        {
    //            delete mTimeLabel;
    //            mTimeLabel = NULL;
    //        }
    //        if(mLapLabel != NULL)
    //        {
    //            delete mLapLabel;
    //            mLapLabel = NULL;
    //        }

}

Viewport* World::getViewPlayer(int number)
{
    switch (number) {
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
}


