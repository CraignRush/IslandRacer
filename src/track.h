#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsScene>
#include <QObject>
#include "checkpoint.h"

enum Underground
{
    Asphalt = 0,
    Grass = 114,
    Sand = 188,
    Water = 252
};

class Track :public QGraphicsScene
{
	Q_OBJECT
private:
    int mWidth;
    int mHeight;
    QImage mBackground;
    QImage mGrayImage;
    Checkpoint* mCheckpoints;

	int mLapNumber = 0;

public:
    Track();
    ~Track();
    //Track(int level);
    //Track(int width, int height, QImage background, QImage grayImage);
    Underground getUnderground(int x, int y);
    QPointF getLastCheckpointPosition();
	void updateCheckpoints(QGraphicsPixmapItem* item);
    void loadTrack(int width, int height, QImage background, QImage grayImage, int checkpointCount, QPoint* position_list, double* angle_list);
signals:
	void LapChanged();
};

#endif // TRACK_H
