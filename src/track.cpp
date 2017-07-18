#include "track.h"
#include "underwatereffect.h"
#include <QColor>
#include <QDebug>

Track::Track()
{
    mWidth = 0;
    mHeight = 0;

    mCheckpoints1 = NULL;
    mCheckpoints2 = NULL;
}

Track::~Track()
{
    if(mCheckpoints1 != NULL)
    {
        for(int i=0; i<mCheckpoints1->GetNumberOfCheckpoints(); i++)
            this->removeItem(mCheckpoints1->GetCheckpoint(i));
        delete mCheckpoints1;
        mCheckpoints1 = NULL;
    }

    if(mCheckpoints2 != NULL)
    {
        for(int i=0; i<mCheckpoints2->GetNumberOfCheckpoints(); i++)
            this->removeItem(mCheckpoints2->GetCheckpoint(i));
        delete mCheckpoints2;
        mCheckpoints2 = NULL;
    }
}


Underground Track::getUnderground(int x, int y)
{
    QRgb pixelRgb = mGrayImage.pixel(x, y);
    QColor pixelColor(pixelRgb);

    //QColor pixelColor = mGrayImage.pixelColor(x, y);
    //int gray = pixelColor.value();
    switch(pixelColor.value())
    {
    case Asphalt: return Asphalt;
    case Grass: return Grass;
    case Sand: return Sand;
    case Water: return Water;
    case Magic: return Magic;
    }

    return Asphalt;
}

void Track::updateCheckpoints(QGraphicsItem* item, int index)
{
    if(index == 1)
    {
        if(!(collidingItems(item).isEmpty()))
         mCheckpoints1->CheckCheckpoint(item);
        int checkpointLaps = mCheckpoints1->GetLaps();
        if(mLapNumber1 != checkpointLaps && checkpointLaps > 0){
            emit LapChanged1();
            mLapNumber1++;
        }
    }
    else if(index == 2)
    {
        if(!(collidingItems(item).isEmpty()))
         mCheckpoints2->CheckCheckpoint(item);
        int checkpointLaps = mCheckpoints2->GetLaps();
        if(mLapNumber2 != checkpointLaps && checkpointLaps > 0){
            emit LapChanged2();
            mLapNumber2++;
        }
    }
}

void Track::ResetCheckpoint(int index)
{
    if(index == 1)
    {
        mCheckpoints1->ResetCheckpointcounter();
    }else if(index == 2)
    {
        mCheckpoints2->ResetCheckpointcounter();
    }
}

WorldPosition Track::getLastCheckpointPosition(int index)
{
    if(index == 1)
        return mCheckpoints1->getLastCheckpointPosition();
    else if (index == 2)
        return mCheckpoints2->getLastCheckpointPosition();
}

void Track::loadTrack(int width, int height, QImage background, QImage grayImage, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions, bool isMultiplayer)
{
    // set variables
    mWidth = width;
    mHeight = height;
    mBackground = background;
    mGrayImage = grayImage;

    // set the scene size to image width/height and set background image
    setSceneRect(0,0,mWidth, mHeight);
    setBackgroundBrush(QBrush(mBackground));

    mLapNumber1 = 0;
    mLapNumber2 = 0;
    // delete old checkpoints and load new ones
    if(mCheckpoints1 != NULL)
    {
        for(int i=0; i<mCheckpoints1->GetNumberOfCheckpoints(); i++)
            this->removeItem(mCheckpoints1->GetCheckpoint(i));
        delete mCheckpoints1;
        mCheckpoints1 = NULL;
    }

    if(mCheckpoints2 != NULL)
    {
        for(int i=0; i<mCheckpoints2->GetNumberOfCheckpoints(); i++)
            this->removeItem(mCheckpoints2->GetCheckpoint(i));
        delete mCheckpoints2;
        mCheckpoints2 = NULL;
    }

    mCheckpoints1 = new Checkpoint(checkpointCount, checkpointPositions, carResetPositions);

    for(int i=0; i<mCheckpoints1->GetNumberOfCheckpoints(); i++)
        this->addItem(mCheckpoints1->GetCheckpoint(i));

    if(isMultiplayer)
    {
        mCheckpoints2 = new Checkpoint(checkpointCount, checkpointPositions, carResetPositions);

        for(int i=0; i<mCheckpoints2->GetNumberOfCheckpoints(); i++)
            this->addItem(mCheckpoints2->GetCheckpoint(i));
    }
}
