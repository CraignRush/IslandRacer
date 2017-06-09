#include "track.h"

Track::Track()
{
    // Create the scene
    setSceneRect(0,0,1280,720); // make the scene 2000x2000 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/images/background.jpeg")));
}
