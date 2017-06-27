#include "checkpoint.h"
#include <QDebug>
#include <QBrush>
#include <QColor>
/*
Checkpoint::Checkpoint()
{

    mCheckpoints = new QGraphicsRectItem[6];

    for(int i= 0; i<6; i++)
    {
        mCheckpoints[i].setRect(0,0,170,5);
        mCheckpoints[i].setBrush(QBrush(QColor(Qt::red)));
        mCheckpoints[i].setOpacity(1.0); // set to 1.0 for debug
    }

    mCheckpoints[0].setRotation(qRadiansToDegrees(1.04));
    mCheckpoints[0].setPos(1371,1503);

    mCheckpoints[1].setRotation(qRadiansToDegrees(1.04));
    mCheckpoints[1].setPos(2703,755);

    mCheckpoints[2].setRotation(qRadiansToDegrees(2.28));
    mCheckpoints[2].setPos(4533,894);

    mCheckpoints[3].setRotation(qRadiansToDegrees(1.62));
    mCheckpoints[3].setPos(4746,2536);

    mCheckpoints[4].setRotation(qRadiansToDegrees(1.44));
    mCheckpoints[4].setPos(2661,1745);

    mCheckpoints[5].setRotation(qRadiansToDegrees(-0.42));
    mCheckpoints[5].setPos(587,2576);

    mNumberOfCheckpoints = 6;

    mCheckpointcounter = 0;
    mLapcounter = 0;

}
*/
Checkpoint::Checkpoint(int checkpointCount, QPoint* position_list, double* angle_list)
{
    mNumberOfCheckpoints = checkpointCount;
    mCheckpoints = new QGraphicsRectItem[checkpointCount];

    for(int i= 0; i<checkpointCount; i++)
    {
        mCheckpoints[i].setRect(0,0,170,5);
        mCheckpoints[i].setBrush(QBrush(QColor(Qt::red)));
        mCheckpoints[i].setOpacity(1.0); // set to 1.0 for debug
        mCheckpoints[i].setRotation(qRadiansToDegrees(angle_list[i]));
        mCheckpoints[i].setPos(position_list[i].x(), position_list[i].y());
    }

    mCheckpointcounter = 0;
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
        if(mLapcounter == 0)
        {
            return mCheckpoints[0].pos();
        }
        else
        {
            return mCheckpoints[mNumberOfCheckpoints-1].pos();
        }
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
