#ifndef UNDERWATEREFFECT_H
#define UNDERWATEREFFECT_H


#include <QGraphicsEffect>
#include <qtgui>
#include <cmath>
#include <QUrl>
#include <QList>
#include <QImage>
#include <QTimeLine>


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

class UnderwaterEffect : public QGraphicsEffect
{
    Q_OBJECT

public:
    UnderwaterEffect(QObject *parent = 0);
    ~UnderwaterEffect();
    void applyUnderwater(const QImage* img, QImage* result1, QImage *result2, int amp, qreal tick);
    void sourceChanged(ChangeFlags flags);
    QRectF boundingRectFor(const QRectF &rect);

protected:
    void draw(QPainter*painter);
private:
    QRectF mRect;
    QImage mImage;
    QImage mModifiedImage1;
    QImage mModifiedImage2;
    QTimeLine* mTimeLine;
    bool mEnableEffect;
    int mAmplitude;
    int mSpeed;

};

#endif // UNDERWATEREFFECT_H
