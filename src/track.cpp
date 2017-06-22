#include "track.h"

Track::Track(int level)
{
    // Create the scene
    setSceneRect(0,0,5760,3240); // make the scene 2000x2000 instead of infinity by infinity (default)
    if (level==1)
    {
    setBackgroundBrush(QBrush(QImage(":/images/images/Monzatextur.png")));
    }
    if (level==2)
    {
    setBackgroundBrush(QBrush(QImage(":/images/images/Hockenheimtextur.png")));
    }
    if (level==3)
    {
    setBackgroundBrush(QBrush(QImage(":/images/images/YasMarinatextur.png")));
    }
    checkpoint = new Checkpoint;

    for(int i=0; i<checkpoint->GetNumberOfCheckpoints(); i++)
        this->addItem(checkpoint->GetCheckpoint(i));
}
