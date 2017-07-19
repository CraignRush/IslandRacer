#include "speedometer.h"

Speedometer::Speedometer(int width, int height, QWidget *parent)
{
    // Set width/height of widget
    mWidth = width;
    mHeight = height;

    // Init background
    setPixmap(QPixmap(":/images/images/speedometer_background.png").scaled(QSize(width,height), Qt::IgnoreAspectRatio));
    setGeometry(20,20,width,height);
    setParent(parent);

    // Init display
    mDisplay = new QLabel();
    mDisplay->setStyleSheet("QLabel { background-color : rgba(255,255,255,30); color : red; }");
    mDisplay->setFont(QFont("GillSansMT",width/15,60));
    mDisplay->setText("000.0km/h");
    mDisplay->adjustSize();
    mDisplay->setParent(this);
    mDisplay->setGeometry(mWidth/2 - mDisplay->size().width()/2, 3*mHeight/4 - 1.2*mDisplay->size().height(), mDisplay->size().width(), mDisplay->size().height());

    // Init needle
    mNeedleImage = new QPixmap(":/images/images/speedometer_needle.png");

    mNeedle = new QLabel();
    mNeedle->setPixmap(mNeedleImage->scaled(QSize(width/15.0,height/2.4), Qt::IgnoreAspectRatio));
    mNeedle->setGeometry(0,0,width, height);
    mNeedle->setParent(this);

    // Init rotation point
    mRotationPoint.setX(width/2);
    mRotationPoint.setY(height/2);
}

Speedometer::~Speedometer()
{
    delete mDisplay;
    mDisplay = NULL;

    delete mNeedleImage;
    mNeedleImage = NULL;

    delete mNeedle;
    mNeedle = NULL;
}

void Speedometer::setVelocity(double velocity)
{
    // Update angle relative to current velocity
    mAngle = mMinAngle + (((velocity - mMinSpeed) / (mMaxSpeed - mMinSpeed)) * (mMaxAngle - mMinAngle));

    // Rotate needle
    QPixmap pixmap(mWidth,mHeight);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    painter.translate(mRotationPoint);
    painter.rotate(mAngle);
    painter.translate(-mRotationPoint.x(), -mRotationPoint.y());
    painter.drawPixmap(mWidth/2-mWidth/30,mHeight/2-0.924*(mHeight/2.4),mWidth/15.0,mHeight/2.4,mNeedleImage->scaled(QSize(mWidth/15.0,mHeight/2.4), Qt::IgnoreAspectRatio));
    mNeedle->setPixmap(pixmap);

    // Update text
    mDisplay->setText(QString::number(velocity, 'f', 1) + "km/h");
}

void Speedometer::setColor(int r, int g, int b, int alpha)
{
    mDisplay->setStyleSheet(QString("QLabel { background-color : rgba(255,255,255,30); color : rgba(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + "," + QString::number(alpha) + "); }"));
}


