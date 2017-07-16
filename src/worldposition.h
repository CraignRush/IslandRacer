#ifndef WORLDPOSITION_H
#define WORLDPOSITION_H

//! This class provides easier handling with car positions
class WorldPosition
{
    int mX;
    int mY;
    double mAngle;

public:
    //! Init x, y and angle value to default 0
    WorldPosition();

    //! Init x, y and angle value selected values
    WorldPosition(int x, int y, double angle);

    //! Get x value
    int x() const;

    //! Set y value
    void setX(int x);

    //! Get x value
    int y() const;

    //! Set y value
    void setY(int y);

    //! Get angle value
    double angle() const;

    //! Set angle value
    void setAngle(double angle);
};

#endif // WORLDPOSITION_H
