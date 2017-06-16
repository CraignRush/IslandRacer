#include "checkpoint.h"
#include <QDebug>

Checkpoint::Checkpoint()
{

    mCheckpoint = new QGraphicsRectItem[6];

    for(int i= 0; i<6; i++)
    {
        mCheckpoint[i].setRect(0,0,170,1);
        mCheckpoint[i].setOpacity(0.0); // set to 1.0 for debug
    }

    mCheckpoint[0].setRotation(qRadiansToDegrees(1.04));
    mCheckpoint[0].setPos(457,409);

    mCheckpoint[1].setRotation(qRadiansToDegrees(1.04));
    mCheckpoint[1].setPos(900,150);

    mCheckpoint[2].setRotation(qRadiansToDegrees(2.28));
    mCheckpoint[2].setPos(1511,298);

    mCheckpoint[3].setRotation(qRadiansToDegrees(1.62));
    mCheckpoint[3].setPos(1432,633);

    mCheckpoint[4].setRotation(qRadiansToDegrees(1.44));
    mCheckpoint[4].setPos(887,464);

    mCheckpoint[5].setRotation(qRadiansToDegrees(-0.42));
    mCheckpoint[5].setPos(172,756);

    mNumberOfCheckpoints = 6;

    mCheckpointcounter = 0;
    mLapcounter = 0;

}

QGraphicsRectItem* Checkpoint::GetCheckpoint(int index)
{
    return &mCheckpoint[index];
}


void Checkpoint::CheckCheckpoint(QGraphicsPixmapItem* car)
{
    for(int i = 0; i<mNumberOfCheckpoints; i++)
    {
        if(mCheckpoint[i].collidesWithItem(car) && mCheckpointcounter == i)
        {
            mCheckpointcounter++;

            if(i==mNumberOfCheckpoints-1) mCheckpointcounter=0;
            if(i==0) mLapcounter++;

            qDebug() << "Checkpoint: " << mCheckpointcounter;
            qDebug() << "Lap: " << mLapcounter;
        }
    }
}

int Checkpoint::GetNumberOfCheckpoints()
{
    return mNumberOfCheckpoints;
}
