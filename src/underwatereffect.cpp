#include "underwatereffect.h"
#include "QDebug"

void UnderwaterEffect::applyUnderwater(const QImage* img, QImage* result1, QImage *result2, int amp, qreal tick)
{
    Q_ASSERT(img);
    Q_ASSERT(result1);
    Q_ASSERT(result2);
    Q_ASSERT(img->size() == result1->size());
    Q_ASSERT(img->size() == result2->size());
    Q_ASSERT(img->format() == QImage::Format_ARGB32);

    int height = img->height();
    int width = img->width();
    int stride =  img->bytesPerLine();

    // shift horizontally
    for (int y = 0; y < height; ++y) {
        const uchar* src = img->scanLine(y);
        uchar* dst = result1->scanLine(y);
        int shift = amp / 2 * (1 + sin((4 * y / qreal(height) + tick) * 2 * M_PI));
        int offset = 4 * shift;
        memcpy(dst + offset, src, img->bytesPerLine() - offset);
    }

    // shift vertically
    for (int x = 0; x < width; ++x) {
        int shift = amp / 2 * (1 + sin((4 * x / qreal(width) + tick) * 2 * M_PI));
        const uchar* src = result1->scanLine(0) + x * 4;
        uchar* dst = result2->scanLine(shift) + x * 4;
        for (int c = 0; c < height - shift; ++c, dst += stride, src += stride) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
        }
    }

}


UnderwaterEffect::UnderwaterEffect(QObject *parent)
{

    mTimeLine = new QTimeLine(1000, this);
    mTimeLine->setFrameRange(0, 4096);
    mTimeLine->setCurveShape(QTimeLine::LinearCurve);
    mTimeLine->setLoopCount(0);
    connect(mTimeLine, SIGNAL(frameChanged(int)), this, SLOT(update()));

    mEnableEffect = true;
    mAmplitude = 6;
    mSpeed = 1000;

    QPainter* mPainter =  new QPainter();
    updateBoundingRect();
    update();
}


void UnderwaterEffect::draw(QPainter* painter)
{
    QPixmap px = sourcePixmap();
    mImage = px.toImage();
    mImage = mImage.convertToFormat(QImage::Format_ARGB32);

     mModifiedImage1 = mImage;
     mModifiedImage2 = mImage;

    if (!mEnableEffect) {
        mTimeLine->setPaused(true);
        painter->drawImage(0, 0, mImage);
    } else {
        if (mTimeLine->state() != QTimeLine::Running)
            mTimeLine->start();

        int duration = 4000 - mSpeed + 1000;
        mTimeLine->setDuration(duration);

        int amp = mAmplitude;
        qreal tick = mTimeLine->currentValue();

        if (!mImage.isNull())
            if (!mModifiedImage1.isNull())
                if (!mModifiedImage2.isNull())
                    applyUnderwater(&mImage, &mModifiedImage1, &mModifiedImage2, amp, tick);
        painter->drawImage(0, 0, mModifiedImage2);
    }
}


void UnderwaterEffect::sourceChanged(ChangeFlags flags)
{

}
UnderwaterEffect::~UnderwaterEffect()
{

}


QRectF UnderwaterEffect::boundingRectFor(const QRectF &rect)
{

    return rect;
}
