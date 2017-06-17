#include "world.h"
#include <QDebug>

World::World(int width, int height)
{
    // Set dimensions
    mWidth = width;
    mHeight = height;

    mLoopIntervalTime = 30;
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

    // Init variables for start sequence
    Opacity = 1.0f;
    mStartCounter = 390;    // 3.9 sec --> short delay before counter begins
    mCounter = new QGraphicsTextItem;
    mCounter->setScale(10);
    mCounter->setPos(mWidth/2-70,mHeight/2-100);
    mTrack->addItem(mCounter);

    // Init and start timer for game loop and start loop
    mTimer = new QTimer(this);
    mStartTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    connect(mStartTimer, SIGNAL(timeout()), this, SLOT(startLoop()));
    mCar->render(); // necessary to init start position of the car
    mStartTimer->start(10);


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
    if(!(mTrack->collidingItems(mCar).isEmpty()))
        mTrack->checkpoint->CheckCheckpoint(mCar);
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
        mTimer->start(mLoopIntervalTime);
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
    }

}
