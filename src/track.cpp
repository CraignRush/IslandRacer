#include "track.h"
#include <QColor>
#include <QDebug>

Track::Track()
{
    mWidth = 0;
    mHeight = 0;
}

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
    mCheckpoints = new Checkpoint;

    for(int i=0; i<mCheckpoints->GetNumberOfCheckpoints(); i++)
        this->addItem(mCheckpoints->GetCheckpoint(i));
}

Track::Track(int width, int height, QImage background, QImage grayImage)
{
    loadTrack(width, height, background, grayImage);
}

Underground Track::getUnderground(int x, int y)
{
    QColor pixelColor = mGrayImage.pixelColor(x, y);
    int gray = pixelColor.value();
    switch(pixelColor.value())
    {
    case Asphalt: return Asphalt;
    case Grass: return Grass;
    case Sand: return Sand;
    case Water: return Water;
    }

//    Underground underground;

//    switch(mGrayImage.pixelxelelColor(x, y))
//    {
//    case :
//    }

    qDebug() << "Underground Color: " << gray;

    return Asphalt;
}

void Track::updateCheckpoints(QGraphicsPixmapItem* item)
{
    if(!(collidingItems(item).isEmpty()))
        mCheckpoints->CheckCheckpoint(item);

}

void Track::loadTrack(int width, int height, QImage background, QImage grayImage)
{
    mWidth = width;
    mHeight = height;
    mBackground = background;
    mGrayImage = grayImage;

    setSceneRect(0,0,mWidth, mHeight);  // set the scene size to image width/height
    setBackgroundBrush(QBrush(mBackground));
}
