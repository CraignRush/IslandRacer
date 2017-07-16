#include "underwatereffect.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QUrl>
#include <QList>
#include <QImage>
#include <QTimeLine>

void applyUnderwater(const QImage* img, QImage* result1, QImage *result2, int amp, qreal tick)
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


UnderwaterEffect::UnderwaterEffect()
{
    setAcceptDrops(true);

    setAttribute(Qt::WA_StaticContents, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);

    mTimeLine = new QTimeLine(1000, this);
    mTimeLine->setFrameRange(0, 4096);
    mTimeLine->setCurveShape(QTimeLine::LinearCurve);
    mTimeLine->setLoopCount(0);
    connect(mTimeLine, SIGNAL(frameChanged(int)), this, SLOT(update()));

    QWidget* toolWidget = new QWidget(this);
    toolWidget->setWindowTitle("Parameters");
    toolWidget->setWindowFlags(Qt::Tool | Qt::WindowTitleHint);
    toolWidget->show();
    QVBoxLayout* toolLayout = new QVBoxLayout;
    toolWidget->setLayout(toolLayout);
    toolLayout->setSizeConstraint(QLayout::SetFixedSize);

    mEnableEffect = new QGroupBox(toolWidget);
    mEnableEffect->setCheckable(true);
    mEnableEffect->setTitle("Enable");
    mEnableEffect->setFlat(true);
    connect(mEnableEffect, SIGNAL(toggled(bool)), SLOT(update()));
    toolLayout->addWidget(mEnableEffect);

    mAmplitudeSlider = new QSlider(toolWidget);
    mAmplitudeSlider->setRange(5, 16);
    mAmplitudeSlider->setOrientation(Qt::Horizontal);
    connect(mAmplitudeSlider, SIGNAL(sliderMoved(int)), SLOT(update()));

    mSpeedSlider = new QSlider(toolWidget);
    mSpeedSlider->setRange(1000, 4000);
    mSpeedSlider->setOrientation(Qt::Horizontal);
    connect(mSpeedSlider, SIGNAL(sliderMoved(int)), SLOT(update()));

    QGridLayout* layout = new QGridLayout;
    mEnableEffect->setLayout(layout);
    layout->addWidget(new QLabel("Amplitude"), 0, 0);
    layout->addWidget(mAmplitudeSlider, 0, 1);
    layout->addWidget(new QLabel("Speed"), 1, 0);
    layout->addWidget(mSpeedSlider, 1, 1);

    toolWidget->adjustSize();

    mEnableEffect->setChecked(true);
    mAmplitudeSlider->setValue(6);
    mSpeedSlider->setValue(1000);
}

void UnderwaterEffect::loadImage(const QImage& image)
{
    mImage = image;
    if (mImage.isNull()) {
        setFixedSize(512, 256);
        setWindowTitle(QString("Can not load %1").arg(mFileName));
    } else {
        QString title = "Underwater Effect ";
        if ((mImage.width() > 640) || (mImage.height() > 480)) {
            qDebug() << "Image is too large. Rescaling....";
            int w = mImage.width();
            mImage = mImage.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            title += QString("[Zoom %1%] ").arg(mImage.width() * 100 / w);
        }
        setWindowTitle(QString("%1: %2 (%3 x %4)").arg(title).arg(mFileName).
                       arg(mImage.width()).arg(mImage.height()));
        setFixedSize(mImage.width(), mImage.height());
        mImage = mImage.convertToFormat(QImage::Format_ARGB32);
    }

    mModifiedImage1 = mImage;
    mModifiedImage2 = mImage;
    update();
}

void UnderwaterEffect::loadImage(const QString& fileName)
{
    mFileName = QFileInfo(fileName).fileName();
    loadImage(QImage(fileName));
}

void UnderwaterEffect::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void UnderwaterEffect::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.count()) {
        QString fname = urls[0].toLocalFile();
        if (event->mimeData()->hasImage()) {
            QImage img = qvariant_cast<QImage>(event->mimeData()->imageData());
            mFileName = QFileInfo(fname).fileName();
            loadImage(img);
        } else
            loadImage(fname);
        event->acceptProposedAction();
    }
}

void UnderwaterEffect::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (!mEnableEffect->isChecked()) {
        mTimeLine->setPaused(true);
        painter.drawImage(0, 0, mImage);
    } else {
        if (mTimeLine->state() != QTimeLine::Running)
            mTimeLine->start();
        int speed = mSpeedSlider->value();
        int duration = mSpeedSlider->maximum() - speed + mSpeedSlider->minimum();
        mTimeLine->setDuration(duration);

        int amp = mAmplitudeSlider->value();
        qreal tick = mTimeLine->currentValue();
        if (!mImage.isNull())
            if (!mModifiedImage1.isNull())
                if (!mModifiedImage2.isNull())
                    applyUnderwater(&mImage, &mModifiedImage1, &mModifiedImage2, amp, tick);
        painter.drawImage(0, 0, mModifiedImage2);
    }
}
