#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsScene>
#include "checkpoint.h"

enum Underground
{
    Asphalt = 0, // (Monza), 4
    Grass = 112, // (Monza), 114
    Sand = 188, // (Monza), 185
    Water = 249 // (Monza), 252
};

class Track : public QGraphicsScene
{
private:
    int mWidth;
    int mHeight;
    QImage mBackground;
    QImage mGrayImage;
    Checkpoint* mCheckpoints;

public:
    Track();
    ~Track();
    //Track(int level);
    //Track(int width, int height, QImage background, QImage grayImage);
    Underground getUnderground(int x, int y);
	int updateCheckpoints(QGraphicsPixmapItem* item);
    void loadTrack(int width, int height, QImage background, QImage grayImage, int checkpointCount, QPoint* position_list, double* angle_list);

};

#endif // TRACK_H
