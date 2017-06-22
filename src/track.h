#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsScene>
#include "checkpoint.h"

class Track : public QGraphicsScene
{
public:
    Track(int level);
    Checkpoint* checkpoint;
};

#endif // TRACK_H
