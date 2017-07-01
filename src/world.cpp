#include "world.h"
#include <QDebug>
#include <QLabel>

World::World(int width, int height) : mWidth{width}, mHeight{height}
{
    // set window title from src.exe to IslandRacer
    setWindowTitle(tr("IslandRacer"));

    // Create Box2D world object (zero gravity)
	mWorld = new b2World(b2Vec2(0.0f, 0.0f));

	// Create track
	mTrack = new Track();

    // Create cars
    mCar1 = new Car(mWorld, mTrack);
    mCar2 = new Car(mWorld, mTrack);

    // Add the cars to the track/scene
    mTrack->addItem(mCar1);
    mTrack->addItem(mCar2);

    // Create views for the player
    mViewPlayer1 = new Viewport(mWidth/2, mHeight, mTrack);
    mViewPlayer2 = new Viewport(mWidth/2, mHeight, mTrack);

    // Init input state
    mCurrentInputStatePlayer1 = None;
    mCurrentInputStatePlayer2 = None;

    // Set up layouts and widgets to display
    mMainLayout = new QStackedLayout(this);
    mViewportLayout = new QHBoxLayout(this);
    mCounterLayout = new QHBoxLayout(this);
    mMainWidget = new QWidget();
    mViewportWidget = new QWidget();
    mCounterWidget = new QWidget();
    mOpacityEffect = new QGraphicsOpacityEffect();
    //mBlurEffect = new QGraphicsBlurEffect();

    // Create horizontal border line between the two viewports
    QFrame* line = new QFrame();
    //line->setFrameShape(QFrame::VLine);
    line->setFixedWidth(10);
    //line->setFrameShadow(QFrame::Sunken);
    // set black background of line
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    line->setAutoFillBackground(true);
    line->setPalette(pal);

    // Prevent manually scrolling with arrow keys
    mViewPlayer1->setFocusPolicy(Qt::NoFocus);
    mViewPlayer1->setCacheMode(QGraphicsView::CacheNone);
    mViewPlayer2->setFocusPolicy(Qt::NoFocus);
    mViewPlayer2->setCacheMode(QGraphicsView::CacheNone);

    //mBlurEffect->setBlurRadius(10.0f);
    //mBlurEffect->setEnabled(true);
    //mBlurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);

    mViewportLayout->setContentsMargins(0,0,0,0);
    mViewportLayout->addWidget(mViewPlayer2, 0, Qt::AlignLeft);
    mViewportLayout->addWidget(line, 0, Qt::AlignCenter);
    mViewportLayout->addWidget(mViewPlayer1, 0, Qt::AlignRight);

    //mViewportWidget->setGraphicsEffect(mBlurEffect);
    mViewportWidget->setLayout(mViewportLayout);

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

    mMainLayout->setStackingMode(QStackedLayout::StackAll);
    mMainLayout->addWidget(mViewportWidget);
    mMainLayout->addWidget(mCounter);

    mMainWidget->setLayout(mMainLayout);
    setCentralWidget(mMainWidget);

	// create timer for game loop
	mTimer = new QTimer(this);

	// connect game loop to timer
	connect(mTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));

    // Init objects for start countdown
    mStartTimer = NULL;
}

World::~World()
{
    // Delete objects from heap and set pointers to NULL
    delete mCar1;
    mCar1 = NULL;

    delete mCar2;
    mCar2 = NULL;

    delete mWorld;
    mWorld = NULL;

    delete mTimer;
    mTimer = NULL;

    delete mTrack;
    mTrack = NULL;

    if(mCounter != NULL)
    {
        delete mCounter;
        mCounter = NULL;
    }

    if(mStartTimer != NULL)
    {
        delete mStartTimer;
        mStartTimer = NULL;
    }

    if(mCounterWidget != NULL)
    {
        delete mCounterWidget;
        mCounterWidget = NULL;
    }

    if(mOpacityEffect != NULL)
    {
        delete mOpacityEffect;
        mOpacityEffect = NULL;
    }

    delete mViewPlayer1;
    mViewPlayer1 = NULL;

    delete mViewPlayer2;
    mViewPlayer2 = NULL;

    delete mViewportWidget;
    mViewportWidget = NULL;

    delete mViewportLayout;
    mViewportLayout = NULL;

    delete mCounterLayout;
    mCounterLayout = NULL;

    //delete mBlurEffect;
    //mBlurEffect = NULL;

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
    mCar1->updatePosition();
    mViewPlayer1->ensureVisible(mCar1, 300, 400);


    mCar2->computeUserInput(mCurrentInputStatePlayer2);
    mCar2->updatePosition();
    mViewPlayer2->ensureVisible(mCar2, 300, 400);

    // Check for checkpoint collision
    mTrack->updateCheckpoints(mCar1);
    mTrack->updateCheckpoints(mCar2);

    // Render cars on new position
    mCar1->render();
    mCar2->render();

    mViewPlayer1->updateOverlay();
    mViewPlayer2->updateOverlay();
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

        mMainLayout->removeWidget(mCounterWidget);
        delete mCounterWidget;
        mCounterWidget = NULL;

        delete mOpacityEffect;
        mOpacityEffect = NULL;

        delete mCounter;
        mCounter = NULL;
        //mTrack->removeItem(mCounter);
        //delete mCounter;
        //mCounter = NULL;
	}
}

void World::loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, QPoint* checkpoint_list, double* angle_list, QPoint carPosition, double carAngle)
{
    // prepare scene
	mTrack->loadTrack(width, height, QImage(background_path), QImage(gray_path), checkpointCount, checkpoint_list, angle_list);

    // set cars to starting position
    mCar1->setPosition(carPosition.x(), carPosition.y(), carAngle);
    mCar2->setPosition(carPosition.x(), carPosition.y(), carAngle);

    // center cars in view
    mViewPlayer1->centerOn(mCar1);
    mViewPlayer2->centerOn(mCar2);

	// Init variables for start sequence
    mOpacity = 1.0f;
	mStartCounter = 390;    // 3.9 sec --> short delay before counter begins
    //mCounter = new QGraphicsTextItem;
    //mCounter->setScale(10);
    //mTrack->addItem(mCounter);

    // Init lap counter and time
    //mViewPlayer1->initLapCounter;

	// Init and start timer for game loop and start loop
	mStartTimer = new QTimer(this);
	connect(mStartTimer, SIGNAL(timeout()), this, SLOT(startLoop()));
    mStartTimer->start(50);
}

void World::keyPressEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
    case Qt::Key_Escape: // Just for debugging, to close game and get back to menu.
//        hide();
        //mBlurEffect->setEnabled(false);

        mTimer->stop();
        if(mCounter != NULL)
        {
            delete mCounter;
            mCounter = NULL;
        }
        if(mStartTimer != NULL)
        {
            mStartTimer->stop();
            delete mStartTimer;
            mStartTimer = NULL;
        }
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
