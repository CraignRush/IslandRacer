#include "car.h"
#include "world.h"
#include "sound.h"
#include <cmath>
#include <QDebug>
#include <QMetaObject>
#include "worldposition.h"


Car::Car(b2World* world, Track* track, int i) : mWorld{world}, mTrack{track}
{
    if (i==1)
    {
        setPixmap(QPixmap(":/images/images/1car.png").scaled(CAR_WIDTH*PX_TO_M_RATIO, CAR_LENGTH*PX_TO_M_RATIO));
    }
    else if (i==2)
    {
        setPixmap(QPixmap(":/images/images/2car.png").scaled(CAR_WIDTH*PX_TO_M_RATIO, CAR_LENGTH*PX_TO_M_RATIO));
    }
    //setScale(0.05);
    ensureVisible(QRectF(), 500, 400);

    //! define our Main Car Body
    b2BodyDef *bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->linearDamping = 1.0f;
    bodyDef->angularDamping = 50.0f;//7.0f;
    bodyDef->position = mCarPosition;

    //! Add Body to the world
    mBody = mWorld->CreateBody(bodyDef);

    //! Define the wheel bodies
    b2BodyDef *leftWheelDef = new b2BodyDef();
    leftWheelDef->type = b2_dynamicBody;
    leftWheelDef->position = mBody->GetWorldPoint(mLeftFrontWheelPosition);

    b2BodyDef *rightWheelDef = new b2BodyDef();
    rightWheelDef->type = b2_dynamicBody;
    rightWheelDef->position = mBody->GetWorldPoint(mRightFrontWheelPosition);

    b2BodyDef *leftRearWheelDef = new b2BodyDef();
    leftRearWheelDef->type = b2_dynamicBody;
    leftRearWheelDef->position = mBody->GetWorldPoint(mLeftRearWheelPosition);

    b2BodyDef *rightRearWheelDef = new b2BodyDef();
    rightRearWheelDef->type = b2_dynamicBody;
    rightRearWheelDef->position = mBody->GetWorldPoint(mRightRearWheelPosition);

    mLeftWheel = mWorld->CreateBody(leftWheelDef);
    mRightWheel = mWorld->CreateBody(rightWheelDef);
    mLeftRearWheel = mWorld->CreateBody(leftRearWheelDef);
    mRightRearWheel = mWorld->CreateBody(rightRearWheelDef);

    //! define shapes of car main body and wheels
    b2PolygonShape *boxDef = new b2PolygonShape();
    boxDef->SetAsBox(CAR_WIDTH/2.0f, CAR_LENGTH/2.0f);
    mBody->CreateFixture(boxDef,(CAR_WEIGHT - 4*TYRE_WEIGHT) / (CAR_WIDTH*CAR_LENGTH));

    //Left Wheel shape
    b2PolygonShape *leftWheelShapeDef = new b2PolygonShape();
    leftWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mLeftWheel->CreateFixture(leftWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //Right Wheel shape
    b2PolygonShape *rightWheelShapeDef = new b2PolygonShape();
    rightWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mRightWheel->CreateFixture(rightWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //Left Rear Wheel shape
    b2PolygonShape *leftRearWheelShapeDef = new b2PolygonShape();
    leftRearWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mLeftRearWheel->CreateFixture(leftRearWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //Right Rear Wheel shape
    b2PolygonShape *rightRearWheelShapeDef = new b2PolygonShape();
    rightRearWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mRightRearWheel->CreateFixture(rightRearWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //! Create rotatable joints for the front wheels
    b2RevoluteJointDef *leftJointDef = new b2RevoluteJointDef();
    leftJointDef->Initialize(mBody, mLeftWheel, mLeftWheel->GetWorldCenter());
    leftJointDef->enableMotor = true;
    leftJointDef->maxMotorTorque = MAX_TORQUE;

    b2RevoluteJointDef *rightJointDef = new b2RevoluteJointDef();
    rightJointDef->Initialize(mBody, mRightWheel, mRightWheel->GetWorldCenter());
    rightJointDef->enableMotor = true;
    rightJointDef->maxMotorTorque = MAX_TORQUE;

    //! Add joints to the world
    mLeftJoint = (b2RevoluteJoint*) mWorld->CreateJoint(leftJointDef);
    mRightJoint = (b2RevoluteJoint*) mWorld->CreateJoint(rightJointDef);

    //! Define rear wheel static joints with only one degree of freedom
    b2PrismaticJointDef *leftRearJointDef = new b2PrismaticJointDef();
    leftRearJointDef->Initialize(mBody, mLeftRearWheel, mLeftRearWheel->GetWorldCenter(), b2Vec2(0,1));
    leftRearJointDef->enableLimit = true;
    leftRearJointDef->lowerTranslation = 0;
    leftRearJointDef->upperTranslation = 0;

    b2PrismaticJointDef *rightRearJointDef = new b2PrismaticJointDef();
    rightRearJointDef->Initialize(mBody, mRightRearWheel, mRightRearWheel->GetWorldCenter(), b2Vec2(0,1));
    rightRearJointDef->enableLimit = true;
    rightRearJointDef->lowerTranslation = 0;
    rightRearJointDef->upperTranslation = 0;

    //! Add rear wheel joint to the world
    mLeftRearJoint = (b2PrismaticJoint*) mWorld->CreateJoint(leftRearJointDef);
    mRightRearJoint = (b2PrismaticJoint*) mWorld->CreateJoint(rightRearJointDef);

    // connect with sound class
    connect(this, SIGNAL(playCarSound()), Sound::getSoundInstance(this), SLOT(playCarSound()));
    connect(this, SIGNAL(stopCarSound()), Sound::getSoundInstance(this), SLOT(stopCarSound()));

    // delete tmp vars
    delete bodyDef;
    delete leftWheelDef;
    delete rightWheelDef;
    delete leftRearWheelDef;
    delete rightRearWheelDef;
    delete boxDef;
    delete leftWheelShapeDef;
    delete rightWheelShapeDef;
    delete leftRearWheelShapeDef;
    delete rightRearWheelShapeDef;
    delete leftJointDef;
    delete rightJointDef;
    delete leftRearJointDef;
    delete rightRearJointDef;

    //set default values for car params
    mSpeedFac = 1.0;
    mAccelerationFac = 1.0;
    mHandlingFac = 1.0;
}

Car::~Car()
{

}

void Car::render()
{
    //! Get position of main car body and scale 1m = 20 px
    b2Vec2 pos = mBody->GetPosition();
    setPos((pos.x - (CAR_WIDTH / 2.0f)) * PX_TO_M_RATIO, (pos.y - (CAR_LENGTH / 2.0f)) * PX_TO_M_RATIO);
    setRotation(mBody->GetAngle() * 360.0 / (2.0 * 3.141592) + CAR_ROTATION_ANGLE);
}


void Car::computeUserInput(InputState input)
{
    /*    qDebug() << "Left Wheel Position: " << leftWheel->GetPosition().x << ", " << leftWheel->GetPosition().y;
    qDebug() << "Right Wheel Position: " << rightWheel->GetPosition().x <<", " <<  rightWheel->GetPosition().y;
    qDebug() << "Car mBody Position: " << mBody->GetPosition().x <<", " <<  mBody->GetPosition().y;
    qDebug() << "Car mBody Angle: " << mBody->GetAngle();
    qDebug() << "RW Angle: " << rightWheel->GetAngle();
    qDebug() << "RW Angle: " << rightWheel->GetTransform().q.GetAngle();
    qDebug() << "LW Angle: " << leftWheel->GetAngle();
    qDebug() << "LW Angle: " << leftWheel->GetTransform().q.GetAngle();
    qDebug() << "RRW Angle: " << rightRearWheel->GetAngle();
    qDebug() << "RRW Angle: " << rightRearWheel->GetTransform().q.GetAngle();
    qDebug() << "LRW Angle: " << leftRearWheel->GetAngle();
    qDebug() << "LRW Angle: " << leftRearWheel->GetTransform().q.GetAngle();*/

    //qDebug() << "Speed: " << mBody->GetLinearVelocity().x << "," << mBody->GetLinearVelocity().y;

    switch(input)
    {
    case Accelerate:
        if(mEngineSpeed > 0)
            mEngineSpeed = 0.0f;
        if(mEngineSpeed > -HORSEPOWERS*mSpeedFac)
            mEngineSpeed -= 400*1.f/(abs(mEngineSpeed)*0.01f+1.f)*mAccelerationFac;
        mSteeringAngle = 0.0f;
        break;
    case AccelerateSteerLeft:
        if(mEngineSpeed > 0)
            mEngineSpeed = 0.0f;
        if(mEngineSpeed > -HORSEPOWERS*mSpeedFac)
            mEngineSpeed -= 400*1.f/(abs(mEngineSpeed)*0.01f+1.f)*mAccelerationFac;
        mSteeringAngle = -MAX_STEER_ANGLE*mHandlingFac; //*(1.f/(qPow(0.06f*mBody->GetLinearVelocity().Length()*abs(mEngineSpeed)/HORSEPOWERS,3)+1.f));
        break;
    case AccelerateSteerRight:
        if(mEngineSpeed > 0)
            mEngineSpeed = 0.0f;
        if(mEngineSpeed > -HORSEPOWERS*mSpeedFac)
            mEngineSpeed -= 400*1.f/(abs(mEngineSpeed)*0.01f+1.f)*mAccelerationFac;
        mSteeringAngle = MAX_STEER_ANGLE*mHandlingFac; //*(1.f/(qPow(0.06f*mBody->GetLinearVelocity().Length()*abs(mEngineSpeed)/HORSEPOWERS,3)+1.f));
        break;
    case Break:
        if(mEngineSpeed < 0)
            mEngineSpeed = 0.0f;
        if(mEngineSpeed < HORSEPOWERS*mSpeedFac/2)
            mEngineSpeed += 200*1.f/(abs(mEngineSpeed)*0.01f+1.f)*mAccelerationFac;
        mSteeringAngle = 0.0f;
        break;
    case BreakSteerLeft:
        if(mEngineSpeed < 0)
            mEngineSpeed = 0.0f;
        if(mEngineSpeed < HORSEPOWERS*mSpeedFac/2)
            mEngineSpeed += 200*1.f/(abs(mEngineSpeed)*0.01f+1.f)*mAccelerationFac;
        mSteeringAngle = -MAX_STEER_ANGLE*mHandlingFac; //*(1.f/(qPow(0.06f*mBody->GetLinearVelocity().Length()*abs(mEngineSpeed)/HORSEPOWERS,3)+1.f));
        break;
    case BreakSteerRight:
        if(mEngineSpeed < 0)
            mEngineSpeed = 0.0f;
        if(mEngineSpeed < HORSEPOWERS*mSpeedFac/2)
            mEngineSpeed += 200*1.f/(abs(mEngineSpeed)*0.01f+1.f)*mAccelerationFac;
        mSteeringAngle = MAX_STEER_ANGLE*1.5; //*(1.f/(qPow(0.06f*mBody->GetLinearVelocity().Length()*abs(mEngineSpeed)/HORSEPOWERS,3)+1.f));
        break;
    case None:
        //mEngineSpeed = 0.0f;
        if(mEngineSpeed < -20.0f)
            mEngineSpeed += 20+mBody->GetLinearVelocity().Length()*3;
        else if(mEngineSpeed > 20.0f)
            mEngineSpeed -= 20+mBody->GetLinearVelocity().Length()*3;
        else
            mEngineSpeed = 0.0f;
        mSteeringAngle = 0.0f;
        break;
    case SteerLeft:
        mSteeringAngle = -MAX_STEER_ANGLE*mHandlingFac; //*(1.f/(qPow(0.06f*mBody->GetLinearVelocity().Length()*abs(mEngineSpeed)/HORSEPOWERS,3)+1.f));
        if(mEngineSpeed < -20.0f)
            mEngineSpeed += 20+mBody->GetLinearVelocity().Length()*3;
        else if(mEngineSpeed > 20.0f)
            mEngineSpeed -= 20+mBody->GetLinearVelocity().Length()*3;
        else
            mEngineSpeed = 0.0f;
        break;
    case SteerRight:
        mSteeringAngle = MAX_STEER_ANGLE*mHandlingFac; //*(1.f/(qPow(0.06f*mBody->GetLinearVelocity().Length()*abs(mEngineSpeed)/HORSEPOWERS,3)+1.f));
        if(mEngineSpeed < -20.0f)
            mEngineSpeed += 20+mBody->GetLinearVelocity().Length()*3;
        else if(mEngineSpeed > 20.0f)
            mEngineSpeed -= 20+mBody->GetLinearVelocity().Length()*3;
        else
            mEngineSpeed = 0.0f;
        break;
    }
}

void Car::computeUndergroundImpact(int index)
{
    Underground underground;

    underground = mTrack->getUnderground(pos().x()+CAR_WIDTH*PX_TO_M_RATIO/2.0f*qCos(qDegreesToRadians(rotation()))-CAR_LENGTH*PX_TO_M_RATIO/2.0f*qSin(qDegreesToRadians(rotation())), pos().y()+CAR_WIDTH*PX_TO_M_RATIO/2.0f*qSin(qDegreesToRadians(rotation()))+CAR_LENGTH*PX_TO_M_RATIO/2.0f*qCos(qDegreesToRadians(rotation())));

    switch(underground)
    {
    case Asphalt:
        mBody->SetLinearDamping(1.0f);
        //mBody->SetAngularDamping(7.0f);
        break;
    case Grass:
        mBody->SetLinearDamping(1.8f);
        //mBody->SetAngularDamping(8.5f);
        break;
    case Sand:
        mBody->SetLinearDamping(2.5f);
        //mBody->SetAngularDamping(10.0f);
        break;
    case Water:
        WorldPosition pos = mTrack->getLastCheckpointPosition(index);
        mEngineSpeed = 0.0f;
        setPosition(pos.x(), pos.y(), pos.angle());
        break;
    }
}

void Car::updatePosition(int index)
{
    // kill orthogonal velocity to avoid sliding
    killOrthogonalVelocity(mLeftWheel);
    killOrthogonalVelocity(mRightWheel);
    killOrthogonalVelocity(mLeftRearWheel);
    killOrthogonalVelocity(mRightRearWheel);

    // compute acceleration and steering forces
    computeUndergroundImpact(index);

    computeSteering();
    computeDriving();

}

// x, y in pixels
void Car::setPosition(int x, int y, double angle)
{
    // Destroy old joints, bodies
    mWorld->DestroyJoint(mLeftJoint);
    mWorld->DestroyJoint(mRightJoint);
    mWorld->DestroyJoint(mLeftRearJoint);
    mWorld->DestroyJoint(mRightRearJoint);
    mWorld->DestroyBody(mLeftWheel);
    mWorld->DestroyBody(mRightWheel);
    mWorld->DestroyBody(mLeftRearWheel);
    mWorld->DestroyBody(mRightRearWheel);
    mWorld->DestroyBody(mBody);

    mCarPosition = b2Vec2((((float) x) / PX_TO_M_RATIO) + (CAR_WIDTH/2.0f), (((float) y) / PX_TO_M_RATIO) + (CAR_LENGTH/2.0f));

    // Create new one on new position
    b2BodyDef *bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->linearDamping = 1;
    bodyDef->angularDamping = 7;
    bodyDef->position = mCarPosition;
    bodyDef->angle = angle;

    //! Add Body to the world
    mBody = mWorld->CreateBody(bodyDef);

    //! Define the wheel bodies
    b2BodyDef *leftWheelDef = new b2BodyDef();
    leftWheelDef->type = b2_dynamicBody;
    leftWheelDef->position = mBody->GetWorldPoint(mLeftFrontWheelPosition);
    leftWheelDef->angle = angle;

    b2BodyDef *rightWheelDef = new b2BodyDef();
    rightWheelDef->type = b2_dynamicBody;
    rightWheelDef->position = mBody->GetWorldPoint(mRightFrontWheelPosition);
    rightWheelDef->angle = angle;

    b2BodyDef *leftRearWheelDef = new b2BodyDef();
    leftRearWheelDef->type = b2_dynamicBody;
    leftRearWheelDef->position = mBody->GetWorldPoint(mLeftRearWheelPosition);
    leftRearWheelDef->angle = angle;

    b2BodyDef *rightRearWheelDef = new b2BodyDef();
    rightRearWheelDef->type = b2_dynamicBody;
    rightRearWheelDef->position = mBody->GetWorldPoint(mRightRearWheelPosition);
    rightRearWheelDef->angle = angle;

    mLeftWheel = mWorld->CreateBody(leftWheelDef);
    mRightWheel = mWorld->CreateBody(rightWheelDef);
    mLeftRearWheel = mWorld->CreateBody(leftRearWheelDef);
    mRightRearWheel = mWorld->CreateBody(rightRearWheelDef);

    //! define shapes of car main body and wheels
    b2PolygonShape *boxDef = new b2PolygonShape();
    boxDef->SetAsBox(CAR_WIDTH/2.0f, CAR_LENGTH/2.0f);
    mBody->CreateFixture(boxDef,(CAR_WEIGHT - 4*TYRE_WEIGHT) / (CAR_WIDTH*CAR_LENGTH));

    //Left Wheel shape
    b2PolygonShape *leftWheelShapeDef = new b2PolygonShape();
    leftWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mLeftWheel->CreateFixture(leftWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //Right Wheel shape
    b2PolygonShape *rightWheelShapeDef = new b2PolygonShape();
    rightWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mRightWheel->CreateFixture(rightWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //Left Rear Wheel shape
    b2PolygonShape *leftRearWheelShapeDef = new b2PolygonShape();
    leftRearWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mLeftRearWheel->CreateFixture(leftRearWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //Right Rear Wheel shape
    b2PolygonShape *rightRearWheelShapeDef = new b2PolygonShape();
    rightRearWheelShapeDef->SetAsBox(TYRE_WIDTH/2.0f, TYRE_LENGTH/2.0f);
    mRightRearWheel->CreateFixture(rightRearWheelShapeDef,TYRE_WEIGHT / (TYRE_WIDTH*TYRE_LENGTH));

    //! Create rotatable joints for the front wheels
    b2RevoluteJointDef *leftJointDef = new b2RevoluteJointDef();
    leftJointDef->Initialize(mBody, mLeftWheel, mLeftWheel->GetWorldCenter());
    leftJointDef->enableMotor = true;
    leftJointDef->maxMotorTorque = MAX_TORQUE;

    b2RevoluteJointDef *rightJointDef = new b2RevoluteJointDef();
    rightJointDef->Initialize(mBody, mRightWheel, mRightWheel->GetWorldCenter());
    rightJointDef->enableMotor = true;
    rightJointDef->maxMotorTorque = MAX_TORQUE;

    //! Add joints to the world
    mLeftJoint = (b2RevoluteJoint*) mWorld->CreateJoint(leftJointDef);
    mRightJoint = (b2RevoluteJoint*) mWorld->CreateJoint(rightJointDef);

    //! Define rear wheel static joints with only one degree of freedom
    b2PrismaticJointDef *leftRearJointDef = new b2PrismaticJointDef();
    leftRearJointDef->Initialize(mBody, mLeftRearWheel, mLeftRearWheel->GetWorldCenter(), mBody->GetWorldVector(b2Vec2(0.0f, 1.0f)));
    leftRearJointDef->localAxisA.Set(0.0f, 1.0f);
    leftRearJointDef->enableLimit = true;
    leftRearJointDef->lowerTranslation = 0;
    leftRearJointDef->upperTranslation = 0;

    b2PrismaticJointDef *rightRearJointDef = new b2PrismaticJointDef();
    rightRearJointDef->Initialize(mBody, mRightRearWheel, mRightRearWheel->GetWorldCenter(), mBody->GetWorldVector(b2Vec2(0.0f,1.0f)));
    rightRearJointDef->localAxisA.Set(0.0f, 1.0f);
    rightRearJointDef->enableLimit = true;
    rightRearJointDef->lowerTranslation = 0;
    rightRearJointDef->upperTranslation = 0;

    //! Add rear wheel joint to the world
    mLeftRearJoint = (b2PrismaticJoint*) mWorld->CreateJoint(leftRearJointDef);
    mRightRearJoint = (b2PrismaticJoint*) mWorld->CreateJoint(rightRearJointDef);

    // render new car position
    render();

    // delete tmp vars
    delete bodyDef;
    delete leftWheelDef;
    delete rightWheelDef;
    delete leftRearWheelDef;
    delete rightRearWheelDef;
    delete boxDef;
    delete leftWheelShapeDef;
    delete rightWheelShapeDef;
    delete leftRearWheelShapeDef;
    delete rightRearWheelShapeDef;
    delete leftJointDef;
    delete rightJointDef;
    delete leftRearJointDef;
    delete rightRearJointDef;
}

void Car::setPosition(WorldPosition position)
{
    setPosition(position.x(), position.y(), position.angle());
}

//This function applies a "friction" in a direction orthogonal to the mBody's axis.
void Car::killOrthogonalVelocity(b2Body *targetBody){

    //! Get the normal vector "in sideway axis" of each wheel in world coordinates
    b2Vec2 currentRightNormal = targetBody->GetWorldVector(b2Vec2(1,0));
    //! Get the vector of velocity in the normal's direction
    b2Vec2 lateralVelocity =  b2Dot(currentRightNormal, targetBody->GetLinearVelocity()) * currentRightNormal;
    //! Compute counter impulse to compensate lateral velocity in each time step
    b2Vec2 impulse = targetBody->GetMass() * -lateralVelocity;

    //! Allow drifting above a MAX_LATERAL_IMPULSE
    if (impulse.Length() > MAX_LATERAL_IMPULSE*mHandlingFac)
        impulse *= MAX_LATERAL_IMPULSE*mHandlingFac / impulse.Length();

    //! Apply the linear impulse to each bodys center
    targetBody->ApplyLinearImpulseToCenter(impulse,true);
    //! Cancel the angular impulse by computing it through "Trägheitsmoment" * "Winkelgeschwindigkeit"
    //! 0.1f through trial and error
    targetBody->ApplyAngularImpulse(0.1f * targetBody->GetInertia() * -targetBody->GetAngularVelocity(), true);
}

void Car::computeDriving(){
    //! Driving
    mLeftWheel->ApplyForceToCenter(mEngineSpeed * mLeftWheel->GetWorldVector(b2Vec2(0,1)),true);
    mLeftRearWheel->ApplyForceToCenter(mEngineSpeed * mLeftRearWheel->GetWorldVector(b2Vec2(0,1)),true);
    mRightWheel->ApplyForceToCenter(mEngineSpeed * mRightWheel->GetWorldVector(b2Vec2(0,1)),true);
    mRightRearWheel->ApplyForceToCenter(mEngineSpeed * mRightRearWheel->GetWorldVector(b2Vec2(0,1)),true);
}

void Car::computeSteering(){
    //! Set motor speed of both revolute joints in relation to desired steering angle
    mSpeed = mSteeringAngle - mLeftJoint->GetJointAngle();
    mLeftJoint->SetMotorSpeed(mSpeed * STEER_SPEED);
    mSpeed = mSteeringAngle - mRightJoint->GetJointAngle();
    mRightJoint->SetMotorSpeed(mSpeed * STEER_SPEED);
}

void Car::setCarParams(int speedValue, int accelerationValue, int handlingValue){
    mSpeedFac = 1.0f + 0.03f * speedValue;
    mAccelerationFac = 1.0f + 0.1f * accelerationValue;
    mHandlingFac = 1.0f + 0.05f * handlingValue;

    mEngineSpeed = 0.0f;
}
