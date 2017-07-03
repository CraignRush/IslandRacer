#ifndef CHECKPOINT_H
#define CHECKPOINT_H


#include <QGraphicsRectItem>
#include <QtMath>
#include "worldposition.h"

class Checkpoint : QGraphicsRectItem
{
private:
    int mCheckpointcounter;
    int mNumberOfCheckpoints;
    int mLapcounter;
    QGraphicsRectItem* mCheckpoints;

public:
    //Checkpoint();
    Checkpoint(int checkpointCount, WorldPosition* checkpointPositions);
    QGraphicsRectItem* GetCheckpoint(int index);
    void CheckCheckpoint(QGraphicsPixmapItem*);
    int GetNumberOfCheckpoints();
    QPointF getLastCheckpointPosition();
	int GetLaps();
};

#endif // CHECKPOINT_H
