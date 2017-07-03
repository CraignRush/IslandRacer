#include "checkpoint.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

Checkpoint::Checkpoint(int checkpointCount, WorldPosition* checkpointPositions)
{
    mNumberOfCheckpoints = checkpointCount;
    mCheckpoints = new QGraphicsRectItem[checkpointCount];

    for(int i= 0; i<checkpointCount; i++)
    {
        mCheckpoints[i].setRect(0,0,600,5);
        mCheckpoints[i].setBrush(QBrush(QColor(Qt::red)));
        mCheckpoints[i].setOpacity(1.0); // set to 1.0 for debug
        mCheckpoints[i].setRotation(qRadiansToDegrees(checkpointPositions[i].angle()));
        mCheckpoints[i].setPos(checkpointPositions[i].x(), checkpointPositions[i].y());
    }

    mCheckpointcounter = 1;
    mLapcounter = 0;
}

QGraphicsRectItem* Checkpoint::GetCheckpoint(int index)
{
    return &mCheckpoints[index];
}

void Checkpoint::CheckCheckpoint(QGraphicsPixmapItem* car)
{
    for(int i = 0; i<mNumberOfCheckpoints; i++)
    {
        if(mCheckpoints[i].collidesWithItem(car) && mCheckpointcounter == i)
        {
            mCheckpointcounter++;

            if(i==mNumberOfCheckpoints-1)
                mCheckpointcounter=0;
            if(i==0)
                mLapcounter++;

            qDebug() << "Checkpoint: " << mCheckpointcounter;
            qDebug() << "Lap: " << mLapcounter;
        }
    }
}

int Checkpoint::GetNumberOfCheckpoints()
{
    return mNumberOfCheckpoints;
}

QPointF Checkpoint::getLastCheckpointPosition()
{
    if(mCheckpointcounter == 0)
    {
        return mCheckpoints[mNumberOfCheckpoints-1].pos();
    }
    else
    {
        return mCheckpoints[mCheckpointcounter-1].pos();
    }
}

int Checkpoint::GetLaps()
{
	return mLapcounter;
}
