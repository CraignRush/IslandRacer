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
    bodyDef.position.Set(10.6f, 12.6f); //set the starting position
    bodyDef.angle = -0.54f; //set the starting angle

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
    currentSpeed = 0.0f;
}

void Car::render()
{
    b2Vec2 pos = mCarBody->GetPosition();
    setPos(pos.x * 40.0, pos.y * 40);
    setRotation(mCarBody->GetAngle() * 360.0 / (2.0 * 3.141592));
    //qDebug() << "Angle: " << mCarBody->GetAngle() << "\n";
    ensureVisible(QRectF(), 100, 100);
}

void Car::computeForces(InputState input)
{
    //qDebug() << "Speed: " << currentSpeed;
    switch(input)
    {
    case Accelerate:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        if(currentSpeed < 0.5f && currentSpeed >-0.5f)                  // Init speed, when standing
        {
            currentSpeed = 0.51f;                                       // change init speed (must be greater than condition value)
        } else if(currentSpeed > 0.5f && currentSpeed < 4.0f)           // change if-condition to change max Speed (2nd value)
            currentSpeed += (1/currentSpeed)/5;                         // change equation to change acceleration
        else if(currentSpeed < -0.5f)
            currentSpeed += 0.03f;                                      // linear pos. acceleration if speed is negativ

        break;
    case AccelerateSteerLeft:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(-0.0001f, true);
        if(currentSpeed < 0.5f && currentSpeed >-0.5f)
        {
            currentSpeed = 0.51f;
        } else if(currentSpeed > 0.5f && currentSpeed < 4.0f)
            currentSpeed += (1/currentSpeed)/5;
        else if(currentSpeed < -0.5f)
            currentSpeed += 0.03f;
        break;
    case AccelerateSteerRight:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(0.0001f, true);
        if(currentSpeed < 0.5f && currentSpeed >-0.5f)
        {
            currentSpeed = 0.51f;
        } else if(currentSpeed > 0.5f && currentSpeed < 4.0f)
            currentSpeed += (1/currentSpeed)/5;
        else if(currentSpeed < -0.5f)
            currentSpeed += 0.03f;
        break;
    case Break:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        if(currentSpeed < 0.5f && currentSpeed >-0.5f)
        {
            currentSpeed = -0.51f;
        } else if(currentSpeed < -0.5f && currentSpeed > -2.0f)
            currentSpeed += (1/currentSpeed)/5;
        else if(currentSpeed > 0.5f)
            currentSpeed += -0.03f;
        break;
    case BreakSteerLeft:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(-0.0001f, true);
        if(currentSpeed < 0.5f && currentSpeed >-0.5f)
        {
            currentSpeed = -0.51f;
        } else if(currentSpeed < -0.5f && currentSpeed > -2.0f)
            currentSpeed += (1/currentSpeed)/5;
        else if(currentSpeed > 0.5f)
            currentSpeed += -0.03f;
        break;
    case BreakSteerRight:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        mCarBody->ApplyTorque(0.0001f, true);
        if(currentSpeed < 0.5f && currentSpeed >-0.5f)
        {
            currentSpeed = -0.51f;
        } else if(currentSpeed < -0.5f && currentSpeed > -2.0f)
            currentSpeed += (1/currentSpeed)/5;
        else if(currentSpeed > 0.5f)
            currentSpeed += -0.03f;
        break;
    case None:
        mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
        if(currentSpeed > 0.5f || currentSpeed < -0.5f) currentSpeed -= (1/currentSpeed)/2; // let the car roll out
        else currentSpeed = 0.0f;
        break;
    case SteerLeft:
        if(currentSpeed >0.5f || currentSpeed <-0.5f)
        {
            mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
            mCarBody->ApplyTorque(-0.0001f, true);
            currentSpeed -= (1/currentSpeed)/2;
        } else currentSpeed = 0.0f;

        break;
    case SteerRight:
        if(currentSpeed > 0.5f || currentSpeed <-0.5f)
        {
            mCarBody->ApplyForce(mCarBody->GetWorldVector(b2Vec2(currentSpeed/10000.0f,0.0f)), mCarBody->GetWorldCenter(), true);
            mCarBody->ApplyTorque(0.0001f, true);
            currentSpeed -= (1/currentSpeed)/2;
        } else currentSpeed = 0.0f;
        break;

    }
}
