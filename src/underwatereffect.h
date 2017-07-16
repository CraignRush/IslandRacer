#ifndef UNDERWATEREFFECT_H
#define UNDERWATEREFFECT_H

#include <QWidget>
#include <qtgui>
#include <cmath>
#include <QGroupBox>
#include <QSlider>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

class UnderwaterEffect : public QWidget
{
    Q_OBJECT
public:
    UnderwaterEffect();
    void loadImage(const QString& file);
    void loadImage(const QImage& image);
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent* event);
    void paintEvent(QPaintEvent*);

private:
    QString mFileName;
    QImage mImage;
    QImage mModifiedImage1;
    QImage mModifiedImage2;
    QTimeLine* mTimeLine;
    QGroupBox* mEnableEffect;
    QSlider* mAmplitudeSlider;
    QSlider* mSpeedSlider;
};

#endif // UNDERWATEREFFECT_H
