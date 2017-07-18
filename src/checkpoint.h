#ifndef CHECKPOINT_H
#define CHECKPOINT_H


#include <QGraphicsRectItem>
#include <QtMath>
#include "worldposition.h"


//! Creates the checkpoints and provide methods to interact with them
class Checkpoint : QGraphicsRectItem
{
private:
    int mCheckpointcounter;
    int mNumberOfCheckpoints;
    int mLapcounter;
    QGraphicsRectItem* mCheckpoints;
    WorldPosition* mCarResetPositions;

public:
    //! Creats the checkpoints.
    /*! Reset positions are also generated.
     * \param checkpointCount Number of checkpoints
     * \param checkpointPositions Array with x,y and rotation value for each checkpoint
     * \param carResetPositions Array with x.y and roatation value for each reset position
     */
    Checkpoint(int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions);

    //! Returns checkpoint[index]
    QGraphicsRectItem* GetCheckpoint(int index);

    //! Check if QGraphicsItem colides with checkpoint.
    /*! mCheckpointcounter and mLapcounter is increased if necessary.
     */
    void CheckCheckpoint(QGraphicsItem*);

    //! Returns the total number of checkpoints.
    int GetNumberOfCheckpoints();

    //! Set mCheckpointcounter to starting checkpoint
    void ResetCheckpointcounter();

    //! Returns the reset positon of the last checkpoint you pase.
    WorldPosition getLastCheckpointPosition();

    //! Returns your current lap.
	int GetLaps();
};

#endif // CHECKPOINT_H
