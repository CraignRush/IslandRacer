#include "checkpoint.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

Checkpoint::Checkpoint(int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions)
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

    mCarResetPositions = new WorldPosition[checkpointCount];

    for(int i= 0; i<checkpointCount; i++)
    {
        mCarResetPositions[i].setX(carResetPositions[i].x());
        mCarResetPositions[i].setY(carResetPositions[i].y());
        mCarResetPositions[i].setAngle(carResetPositions[i].angle());
    }
    mCheckpointcounter = 1;
    mLapcounter = 0;
}

QGraphicsRectItem* Checkpoint::GetCheckpoint(int index)
{
    return &mCheckpoints[index];
}

void Checkpoint::CheckCheckpoint(QGraphicsItem* car)
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

WorldPosition Checkpoint::getLastCheckpointPosition()
{
    if(mCheckpointcounter == 0)
    {
        return mCarResetPositions[mNumberOfCheckpoints-1];
    }
    else
    {
        return mCarResetPositions[mCheckpointcounter-1];
    }
}

int Checkpoint::GetLaps()
{
	return mLapcounter;
}
