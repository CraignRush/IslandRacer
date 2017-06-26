#ifndef CHECKPOINT_H
#define CHECKPOINT_H


#include <QGraphicsRectItem>
#include <QtMath>

class Checkpoint : QGraphicsRectItem
{
public:
    //Checkpoint();
    Checkpoint(int checkpointCount, QPoint* position_list, double* angle_list);
    QGraphicsRectItem* GetCheckpoint(int index);
    void CheckCheckpoint(QGraphicsPixmapItem*);
    int GetNumberOfCheckpoints();

private:
    int mCheckpointcounter;
    int mNumberOfCheckpoints;
    int mLapcounter;
    QGraphicsRectItem* mCheckpoints;
};

#endif // CHECKPOINT_H
