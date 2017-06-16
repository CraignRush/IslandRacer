#ifndef CHECKPOINT_H
#define CHECKPOINT_H


#include <QGraphicsRectItem>
#include <QtMath>

class Checkpoint : QGraphicsRectItem
{
public:
    Checkpoint();
    QGraphicsRectItem* GetCheckpoint(int index);
    void CheckCheckpoint(QGraphicsPixmapItem*);
    int GetNumberOfCheckpoints();

private:
    int mCheckpointcounter;
    int mNumberOfCheckpoints;
    int mLapcounter;
    QGraphicsRectItem* mCheckpoint;
};

#endif // CHECKPOINT_H
