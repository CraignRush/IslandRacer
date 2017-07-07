#include "track.h"
#include <QColor>
#include <QDebug>

Track::Track()
{
    mWidth = 0;
    mHeight = 0;

    mCheckpoints = NULL;
}

Track::~Track()
{
    if(mCheckpoints != NULL)
    {
        for(int i=0; i<mCheckpoints->GetNumberOfCheckpoints(); i++)
            this->removeItem(mCheckpoints->GetCheckpoint(i));
        delete mCheckpoints;
        mCheckpoints = NULL;
    }
}

/*
Track::Track(int level)
{
    // Create the scene
    setSceneRect(0,0,5760,3240); // make the scene 2000x2000 instead of infinity by infinity (default)
    if (level==1)
    {
    setBackgroundBrush(QBrush(QImage(":/images/images/Monzatextur.png")));
    }
    if (level==2)
    {
    setBackgroundBrush(QBrush(QImage(":/images/images/Hockenheimtextur.png")));
    }
    if (level==3)
    {
    setBackgroundBrush(QBrush(QImage(":/images/images/YasMarinatextur.png")));
    }
    mCheckpoints = new Checkpoint;

    for(int i=0; i<mCheckpoints->GetNumberOfCheckpoints(); i++)
        this->addItem(mCheckpoints->GetCheckpoint(i));
}
*/

/*
Track::Track(int width, int height, QImage background, QImage grayImage)
{
    // add checkpoints
    for(int i=0; i<mCheckpoints->GetNumberOfCheckpoints(); i++)
        this->addItem(mCheckpoints->GetCheckpoint(i));

    loadTrack(width, height, background, grayImage);
}
*/

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
    }

    return Asphalt;
}

void Track::updateCheckpoints(QGraphicsPixmapItem* item)
{
    if(!(collidingItems(item).isEmpty()))
        mCheckpoints->CheckCheckpoint(item);
	int checkpointLaps = mCheckpoints->GetLaps();
	if(mLapNumber != checkpointLaps && checkpointLaps > 0){
		emit LapChanged();
		mLapNumber++;
	}
}

WorldPosition Track::getLastCheckpointPosition()
{
    return mCheckpoints->getLastCheckpointPosition();
}

void Track::loadTrack(int width, int height, QImage background, QImage grayImage, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions)
{
    // set variables
    mWidth = width;
    mHeight = height;
    mBackground = background;
    mGrayImage = grayImage;

    // set the scene size to image width/height and set background image
    setSceneRect(0,0,mWidth, mHeight);
    setBackgroundBrush(QBrush(mBackground));

    mLapNumber = 0;
    // delete old checkpoints and load new ones
    if(mCheckpoints != NULL)
    {
        for(int i=0; i<mCheckpoints->GetNumberOfCheckpoints(); i++)
            this->removeItem(mCheckpoints->GetCheckpoint(i));
        delete mCheckpoints;
    }
    mCheckpoints = new Checkpoint(checkpointCount, checkpointPositions, carResetPositions);

    for(int i=0; i<mCheckpoints->GetNumberOfCheckpoints(); i++)
        this->addItem(mCheckpoints->GetCheckpoint(i));
}
