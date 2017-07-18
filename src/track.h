#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsScene>
#include <QObject>
#include "checkpoint.h"
#include "worldposition.h"

//! Enum for all undergrounds
enum Underground
{
    Asphalt = 0,
    Magic = 70,
    Grass = 114,
    Sand = 188,
    Water = 252
};

//! Provides the scene for the game
class Track :public QGraphicsScene
{
	Q_OBJECT
private:
    int mWidth;
    int mHeight;
    QImage mBackground;
    QImage mGrayImage;
    Checkpoint* mCheckpoints1;
    Checkpoint* mCheckpoints2;

    int mLapNumber1 = 0;
    int mLapNumber2 = 0;

public:
    //! Init values
    Track();
    ~Track();
    //Track(int level);
    //Track(int width, int height, QImage background, QImage grayImage);

    //! Get the underground for position (x,y)
    Underground getUnderground(int x, int y);

    //! Returns the position of the last checkpoint you passed
    /*!
     * \param index Indicates the player (1 or 2)
     */
    WorldPosition getLastCheckpointPosition(int index);

    //! Calls the CheckCheckpoint function in checkpoint class and check if lap has changed
    /*!
     * \param item The car object
     * \param index Indicates the player (1 or 2)
     */
    void updateCheckpoints(QGraphicsItem* item, int index);

    //! Calls the ResetCheckpointcounter function of checkpoint class
    /*!
     * \param index Indicates the player (1 or 2)
     */
    void ResetCheckpoint(int index);

    //! Set up the scene and generating the necessary checkpoints
    /*!
     * \param width Your screen width
     * \param height Your screen height
     * \param background The track image
     * \param grayImage The grey scale image
     * \param checkpointCount Number of checkpoints on selected track
     * \param checkpointPositions Array with position of all checkpoints
     * \param carResetPositions Array with position of all reset positions
     * \param isMultiplayer Indicates if you need elements for SP or MP
     */
    void loadTrack(int width, int height, QImage background, QImage grayImage, int checkpointCount, WorldPosition* checkpointPositions, WorldPosition* carResetPositions, bool isMultiplayer);
signals:

    //! Signal if lap of player 1 has changed
    void LapChanged1();

    //! Signal if lap of player 2 has changed
    void LapChanged2();
};

#endif // TRACK_H
