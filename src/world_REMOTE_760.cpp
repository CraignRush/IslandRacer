#include "world.h"
#include <QDebug>

World::World(int width, int height)
{
    // --- Init class members ---

    // Set dimensions
    mWidth = width;
    mHeight = height;
    //scale(mWidth / 1920.0f * 2.0f,mHeight / 1080.0f * 2.0f);

    showFullScreen();

    mFps = 50;
    mCurrentInputState = None;

    // Create Box2D world object (zero gravity)
    mWorld = new b2World(b2Vec2(0.0f, 0.0f));

    // Create track
    mTrack = new Track();

    // Set track as scene for this view
    setScene(mTrack);

    // Set size for view and disable scrollbars
    setFixedSize(mWidth, mHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create car
    mCar = new Car(mWorld, mTrack);

    // necessary to init start position of the car
    mCar->render();

    // Add the car to the track/scene
    mTrack->addItem(mCar);

    // Center car in view
    centerOn(mCar);

    // Show the scene
    show();

    // create timer for game loop
    mTimer = new QTimer(this);

    // connect game loop to timer
    connect(mTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
}

/*
World::World(int width, int height, int level)
{
    // --- Init class members ---

    // Set dimensions
    mWidth = width;
    mHeight = height;
	//scale(mWidth / 1920.0f * 2.0f,mHeight / 1080.0f * 2.0f);

    mFps = 50;
    mCurrentInputState = None;

    // Create Box2D world object (zero gravity)
    mWorld = new b2World(b2Vec2(0.0f, 0.0f));

    // Create track
    mTrack = new Track();
    //mTrack = new Track(5760, 3240, QImage(":/images/images/Monzatextur.png"), QImage(":/images/images/Monzagrey.png"));

    // Set track as scene for this view
    setScene(mTrack);

    // Set size for view and disable scrollbars
    setFixedSize(mWidth, mHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create car
    mCar = new Car(mWorld, mTrack);

    // necessary to init start position of the car
    mCar->render();

    // Add the car to the track/scene
    mTrack->addItem(mCar);

    // Center car in view
    centerOn(mCar);

    // Show the scene
    show();

    // connect game loop to timer
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
}
*/

World::~World()
{
    delete mWorld;
    mWorld = NULL;

    delete mTrack;
    mTrack = NULL;

    delete mCar;
    mCar = NULL;

    if(mCounter != NULL)
    {
        delete mCounter;
        mCounter = NULL;
    }

    delete mTimer;
    mTimer = NULL;

    delete mStartTimer;
    mStartTimer = NULL;
}

void World::keyPressEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
    case Qt::Key_Escape: // Just for debugging, to close game and get back to menu.
        delete this;
        break;
    case Qt::Key_Left:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case Accelerate:
            mCurrentInputState = AccelerateSteerLeft; break;
        case AccelerateSteerRight:
            mCurrentInputState = Accelerate; break;
        case Break:
            mCurrentInputState = BreakSteerLeft; break;
        case BreakSteerRight:
            mCurrentInputState = Break; break;
        case None:
            mCurrentInputState = SteerLeft; break;
        case SteerRight:
            mCurrentInputState = None; break;
        }
        break;
    case Qt::Key_Right:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case Accelerate:
            mCurrentInputState = AccelerateSteerRight; break;
        case AccelerateSteerLeft:
            mCurrentInputState = Accelerate; break;
        case Break:
            mCurrentInputState = BreakSteerRight; break;
        case BreakSteerLeft:
            mCurrentInputState = Break; break;
        case None:
            mCurrentInputState = SteerRight; break;
        case SteerLeft:
            mCurrentInputState = None; break;
        }
        break;
    case Qt::Key_Up:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case None:
            mCurrentInputState = Accelerate; break;
        case SteerLeft:
            mCurrentInputState = AccelerateSteerLeft; break;
        case SteerRight:
            mCurrentInputState = AccelerateSteerRight; break;
        case Break:
            mCurrentInputState = None; break;
        }
        break;
    case Qt::Key_Down:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case None:
            mCurrentInputState = Break; break;
        case SteerLeft:
            mCurrentInputState = BreakSteerLeft; break;
        case SteerRight:
            mCurrentInputState = BreakSteerRight; break;
        case Accelerate:
            mCurrentInputState = None; break;
        }
        break;
    }
}

void World::keyReleaseEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
    case Qt::Key_Left:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case AccelerateSteerLeft:
            mCurrentInputState = Accelerate; break;
        case BreakSteerLeft:
            mCurrentInputState = Break; break;
        case SteerLeft:
            mCurrentInputState = None; break;
        }
        break;
    case Qt::Key_Right:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case AccelerateSteerRight:
            mCurrentInputState = Accelerate; break;
        case BreakSteerRight:
            mCurrentInputState = Break; break;
        case SteerRight:
            mCurrentInputState = None; break;
        }
        break;
    case Qt::Key_Up:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case Accelerate:
            mCurrentInputState = None; break;
        case AccelerateSteerLeft:
            mCurrentInputState = SteerLeft; break;
        case AccelerateSteerRight:
            mCurrentInputState = SteerRight; break;
        }
        break;
    case Qt::Key_Down:
        // set new state depending on current state
        switch(mCurrentInputState)
        {
        case Break:
            mCurrentInputState = None; break;
        case BreakSteerLeft:
            mCurrentInputState = SteerLeft; break;
        case BreakSteerRight:
            mCurrentInputState = SteerRight; break;
        }
        break;
    }
}

void World::gameLoop()
{
    mWorld->Step(1.0f/mFps, 8, 3);

    mCar->computeUserInput(mCurrentInputState);
    mCar->updatePosition();
    mTrack->updateCheckpoints(mCar);
    mCar->render();
}

void World::startLoop()
{
    if(mStartCounter%100==0 && mStartCounter > 0)
    {
        Opacity=1.0f;
        mCounter->setPlainText(QString::number(mStartCounter/100));
    }
    if(mStartCounter == 0)
    {
        Opacity=1.0f;
        mCounter->setPos(mWidth/2-90,mHeight/2-100);
        mCounter->setPlainText("GO!!");
        mTimer->start(1000.0/mFps);
        mStartTimer->start(20);
    }

    mCounter->setOpacity(Opacity);
    Opacity -= 0.01f;
    mStartCounter--;

    if(mStartCounter == -100)
    {
        mStartTimer->stop();
        mTrack->removeItem(mCounter);
        delete mCounter;
        mCounter = NULL;
    }
}

void World::loadTrack(int width, int height, QString background_path, QString gray_path, int checkpointCount, QPoint* checkpoint_list, double* angle_list, QPoint carPosition, double carAngle)
{
    mTrack->loadTrack(width, height, QImage(background_path), QImage(gray_path), checkpointCount, checkpoint_list, angle_list);
    mCar->startPosition(carPosition.x(), carPosition.y(), carAngle);

    // Init variables for start sequence
    Opacity = 1.0f;
    mStartCounter = 390;    // 3.9 sec --> short delay before counter begins
    mCounter = new QGraphicsTextItem;
    mCounter->setScale(10);
    mCounter->setPos(mWidth/2-70,mHeight/2-100);
    mTrack->addItem(mCounter);

    // Init and start timer for game loop and start loop
    mStartTimer = new QTimer(this);
    connect(mStartTimer, SIGNAL(timeout()), this, SLOT(startLoop()));
    mCar->render(); // necessary to init start position of the car
    mStartTimer->start(10);
}