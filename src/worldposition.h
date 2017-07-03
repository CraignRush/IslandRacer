#ifndef WORLDPOSITION_H
#define WORLDPOSITION_H


class WorldPosition
{
    int mX;
    int mY;
    double mAngle;

public:
    WorldPosition();
    WorldPosition(int x, int y, double angle);

    int x() const;
    void setX(int x);
    int y() const;
    void setY(int y);
    double angle() const;
    void setAngle(double angle);
};

#endif // WORLDPOSITION_H
