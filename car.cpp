#include "car.h"
#include <cmath>
#include <world.h>
#include <QDebug>

Car::Car(b2World* world)
{
    setPixmap(QPixmap(":/images/images/car1.png"));
    setScale(0.05);
    //render();
    //setPos(290,370); // TODO generalize to always be in the middle bottom of screen
    //setRotation(-34.0);
    ensureVisible(QRectF(), 100, 100);

    // set up physical body for simulation
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; //this will be a dynamic body
    bodyDef.position.Set(0.0, 3.0); //set the starting position
    bodyDef.angle = 0; //set the starting angle

    // create body from definition
    mCarBody = world->CreateBody(&bodyDef);

    // create shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f,1.0f);

    // define fixture
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1.0f;
    boxFixtureDef.friction = 0.3f;

    // create fixture and apply to car body
    mCarBody->CreateFixture(&boxFixtureDef);
}

void Car::render()
{
    b2Vec2 pos = mCarBody->GetPosition();
    setPos(pos.x * 40.0, pos.y * 40);
    setRotation(mCarBody->GetAngle() * 360.0 / (2.0 * 3.141592));
    qDebug() << "Angle: " << mCarBody->GetAngle() << "\n";
    ensureVisible(QRectF(), 100, 100);
}

void Car::computeForces(InputState input)
{
    switch(input)
    {
    case Accelerate:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(0.0005f,0.0f)), mCarBody->GetWorldCenter(), true); break;
    case AccelerateSteerLeft:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(0.0005f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(-0.0001f, true); break;
    case AccelerateSteerRight:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(0.0005f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(0.0001f, true); break;
    case Break:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(-0.0005f,0.0f)), mCarBody->GetWorldCenter(), true); break;
    case BreakSteerLeft:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(-0.0005f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(-0.0001f, true); break;
    case BreakSteerRight:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(-0.0005f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(0.0001f, true); break;
    }
}
