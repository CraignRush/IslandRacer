#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QLabel>
#include <QPainter>

class Speedometer : public QLabel
{
    Q_OBJECT

private:
    double mWidth;
    double mHeight;

    QLabel* mNeedle;
    QPixmap* mNeedleImage;
    QPoint mRotationPoint;

    double mAngle;
    const double mMaxAngle = 135.0;
    const double mMinAngle = -135.0;
    const double mMaxSpeed = 350.0;
    const double mMinSpeed = 0.0;

public:
    explicit Speedometer(int width, int height, QWidget *parent = nullptr);
    void setVelocity(double velocity);

signals:

public slots:
};

#endif // SPEEDOMETER_H
