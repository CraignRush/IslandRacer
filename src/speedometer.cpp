#include "speedometer.h"

Speedometer::Speedometer(int width, int height, QWidget *parent)
{
    mWidth = width;
    mHeight = height;

    setPixmap(QPixmap(":/images/images/speedometer_background.png").scaled(QSize(width,height), Qt::IgnoreAspectRatio));
    setGeometry(20,20,width,height);
    setParent(parent);

    mNeedleImage = new QPixmap(":/images/images/speedometer_needle.png");


    mNeedle = new QLabel();
    //mNeedle = new RotationLabel(*mNeedleImage);
 //   mNeedle->setStyleSheet("background: ");
    //mNeedle->setPixmap(QPixmap(":/images/images/speedometer_needle.png").scaled(QSize(width/15.0,height/2.4), Qt::IgnoreAspectRatio));
    mNeedle->setPixmap(mNeedleImage->scaled(QSize(width/15.0,height/2.4), Qt::IgnoreAspectRatio));
    //mNeedle->setAutoFillBackground(true);
    //mNeedle->setGeometry(width/2-width/30,height/2-0.924*(height/2.4),width/15.0,height/2.4);
    mNeedle->setGeometry(0,0,width, height);
    mNeedle->setParent(this);

    mRotationPoint.setX(width/2);
    //mRotationPoint.setY(height/2 - (height/2.4) + 0.924*(height/2.4));
    mRotationPoint.setY(height/2);
}

void Speedometer::setVelocity(double velocity)
{
    mAngle = mMinAngle + (((velocity - mMinSpeed) / (mMaxSpeed - mMinSpeed)) * (mMaxAngle - mMinAngle));

    QPixmap pixmap(mWidth,mHeight);
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);
    painter.translate(mRotationPoint);
    painter.rotate(mAngle);
    painter.translate(-mRotationPoint.x(), -mRotationPoint.y());
    painter.drawPixmap(mWidth/2-mWidth/30,mHeight/2-0.924*(mHeight/2.4),mWidth/15.0,mHeight/2.4,mNeedleImage->scaled(QSize(mWidth/15.0,mHeight/2.4), Qt::IgnoreAspectRatio));

    mNeedle->setPixmap(pixmap);
}
