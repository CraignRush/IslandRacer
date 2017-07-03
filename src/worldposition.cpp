#include "worldposition.h"

WorldPosition::WorldPosition()
{
    mX = 0;
    mY = 0;
    mAngle = 0.0;
}

WorldPosition::WorldPosition(int x, int y, double angle)
{
    mX = x;
    mY = y;
    mAngle = angle;
}

int WorldPosition::x() const
{
    return mX;
}

void WorldPosition::setX(int x)
{
    mX = x;
}

int WorldPosition::y() const
{
    return mY;
}

void WorldPosition::setY(int y)
{
    mY = y;
}

double WorldPosition::angle() const
{
    return mAngle;
}

void WorldPosition::setAngle(double angle)
{
    mAngle = angle;
}
