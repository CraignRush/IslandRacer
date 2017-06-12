#include "world.h"

World::World(int width, int height)
{
    // Set dimensions
    mWidth = width;
    mHeight = height;

    mLoopIntervalTime = 40;
    mCurrentInputState = None;

    // Create Box2D world object
    mWorld = new b2World(b2Vec2(0.0, 0.0));

    // Create track
    mTrack = new Track();

    // Set track as scene for this view
    setScene(mTrack);

    // Set size for view and disable scrollbars
    setFixedSize(mWidth, mHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create car
    mCar = new Car(mWorld);

    // Add the car to the track/scene
    mTrack->addItem(mCar);

    // Center car in view
    centerOn(mCar);

    // Show the scene
    show();

    // Init and start timer for game loop
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    mTimer->start(mLoopIntervalTime);
}

void World::keyPressEvent(QKeyEvent *keyEvent)
{
    // handle key press
    switch(keyEvent->key())
    {
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
    mCar->computeForces(mCurrentInputState);
    mWorld->Step(mLoopIntervalTime, 8, 3);
    mCar->render();
}
