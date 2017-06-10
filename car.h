#ifndef CAR_H
#define CAR_H

#include <QGraphicsPixmapItem>
#include <Box2D/Box2D.h>

class Car : public QGraphicsPixmapItem
{
private:
    b2Body* mCarBody;
    float currentSpeed;

public:
    Car(b2World* world);
    void render();
    void computeForces(enum InputState input);
};

#endif // CAR_H
