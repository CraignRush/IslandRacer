#include "track.h"

Track::Track()
{
    // Create the scene
    setSceneRect(0,0,1920,1080); // make the scene 2000x2000 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/images/Island1.png")));

    checkpoint = new Checkpoint;

    for(int i=0; i<checkpoint->GetNumberOfCheckpoints(); i++)
        this->addItem(checkpoint->GetCheckpoint(i));
}
