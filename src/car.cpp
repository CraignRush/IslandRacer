#include "car.h"
#include "world.h"
#include <cmath>
#include <QDebug>


Car::Car(b2World* world, Track* track) : mWorld{world}, mTrack{track}
{
    setPixmap(QPixmap(":/images/images/car1.png").scaled(1.8f*PX_TO_M_RATIO, 5.0*PX_TO_M_RATIO));
    //setScale(0.05);
	ensureVisible(QRectF(), 300, 300);

	//! define our Main Car Body
	b2BodyDef *bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->linearDamping = 1;
	bodyDef->angularDamping = 7;
	bodyDef->position = CAR_STARTING_POS;

	//! Add Body to the world
    mBody = mWorld->CreateBody(bodyDef);

	//! Define the wheel bodies
	b2BodyDef *leftWheelDef = new b2BodyDef();
	leftWheelDef->type = b2_dynamicBody;
	leftWheelDef->position = CAR_STARTING_POS;
    leftWheelDef->position +=mLeftFrontWheelPosition;

	b2BodyDef *rightWheelDef = new b2BodyDef();
	rightWheelDef->type = b2_dynamicBody;
	rightWheelDef->position = CAR_STARTING_POS;
    rightWheelDef->position += mRightFrontWheelPosition;

	b2BodyDef *leftRearWheelDef = new b2BodyDef();
	leftRearWheelDef->type = b2_dynamicBody;
	leftRearWheelDef->position = CAR_STARTING_POS;
    leftRearWheelDef->position += mLeftRearWheelPosition;

	b2BodyDef *rightRearWheelDef = new b2BodyDef();
	rightRearWheelDef->type = b2_dynamicBody;
	rightRearWheelDef->position = CAR_STARTING_POS;
    rightRearWheelDef->position += mRightRearWheelPosition;

    mLeftWheel = mWorld->CreateBody(leftWheelDef);
    mRightWheel = mWorld->CreateBody(rightWheelDef);
    mLeftRearWheel = mWorld->CreateBody(leftRearWheelDef);
    mRightRearWheel = mWorld->CreateBody(rightRearWheelDef);

	//! define shapes of car main body and wheels
	b2PolygonShape *boxDef = new b2PolygonShape();
    boxDef->SetAsBox(1.8f,5.0f);
	mBody->CreateFixture(boxDef,1.0f);

	//Left Wheel shape
	b2PolygonShape *leftWheelShapeDef = new b2PolygonShape();
	leftWheelShapeDef->SetAsBox(0.2f,0.5f);
    mLeftWheel->CreateFixture(leftWheelShapeDef,1.0f);

	//Right Wheel shape
	b2PolygonShape *rightWheelShapeDef = new b2PolygonShape();
	rightWheelShapeDef->SetAsBox(0.2f,0.5f);
    mRightWheel->CreateFixture(rightWheelShapeDef,1.0f);

	//Left Rear Wheel shape
	b2PolygonShape *leftRearWheelShapeDef = new b2PolygonShape();
	leftRearWheelShapeDef->SetAsBox(0.2f,0.5f);
    mLeftRearWheel->CreateFixture(leftRearWheelShapeDef,1.0f);

	//Right Rear Wheel shape
	b2PolygonShape *rightRearWheelShapeDef = new b2PolygonShape();
	rightRearWheelShapeDef->SetAsBox(0.2f,0.5f);
    mRightRearWheel->CreateFixture(rightRearWheelShapeDef,1.0f);

	//! Create rotatable joints for the front wheels
	b2RevoluteJointDef *leftJointDef = new b2RevoluteJointDef();
    leftJointDef->Initialize(mBody, mLeftWheel, mLeftWheel->GetWorldCenter());
	leftJointDef->enableMotor = true;
	leftJointDef->maxMotorTorque = 200;

	b2RevoluteJointDef *rightJointDef = new b2RevoluteJointDef();
    rightJointDef->Initialize(mBody, mRightWheel, mRightWheel->GetWorldCenter());
	rightJointDef->enableMotor = true;
	rightJointDef->maxMotorTorque = 200;

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
    mWorld->CreateJoint(leftRearJointDef);
    mWorld->CreateJoint(rightRearJointDef);
}

void Car::render()
{
    //! Get position of main car body and scale 1m = 10 px
	b2Vec2 pos = mBody->GetPosition();
	setPos(pos.x * PX_TO_M_RATIO, pos.y * PX_TO_M_RATIO);
	setRotation(mBody->GetAngle() * 360.0 / (2.0 * 3.141592) + CAR_ROTATION_ANGLE);
	ensureVisible(QRectF(), 300, 300);
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
	switch(input)
	{
	case Accelerate:
		mEngineSpeed = -HORSEPOWERS;
		mSteeringAngle = 0.0f;
		break;
	case AccelerateSteerLeft:
		mEngineSpeed = -HORSEPOWERS;
		mSteeringAngle = -MAX_STEER_ANGLE;
		break;
	case AccelerateSteerRight:
		mEngineSpeed = -HORSEPOWERS;
		mSteeringAngle = MAX_STEER_ANGLE;
		break;
	case Break:
		mEngineSpeed = HORSEPOWERS;
		mSteeringAngle = 0.0f;
		break;
	case BreakSteerLeft:
		mEngineSpeed = HORSEPOWERS;
		mSteeringAngle = -MAX_STEER_ANGLE;
		break;
	case BreakSteerRight:
		mEngineSpeed = HORSEPOWERS;
		mSteeringAngle = MAX_STEER_ANGLE;
		break;
	case None:
		mEngineSpeed = 0.0f;
		mSteeringAngle = 0.0f;
		break;
	case SteerLeft:
		mSteeringAngle = -MAX_STEER_ANGLE;
		mEngineSpeed = 0.0f;
		break;
	case SteerRight:
		mSteeringAngle = MAX_STEER_ANGLE;
		mEngineSpeed = 0.0f;
		break;
    }
}

void Car::computeUndergroundImpact()
{
    Underground underground;

    underground = mTrack->getUnderground(pos().x(), pos().y());


    switch(underground)
    {
    case Asphalt:
        mBody->SetLinearDamping(1.0f);
        //mBody->SetAngularDamping(1.0f);
        break;
    case Grass:
        mBody->SetLinearDamping(3.0f);
        //mBody->SetAngularDamping(4.0f);
        break;
    case Sand:
        mBody->SetLinearDamping(5.0f);
        //mBody->SetAngularDamping(7.0f);
        break;
    case Water:
        mBody->SetTransform(b2Vec2(200,150),mBody->GetAngle());
        break;
    }
}

void Car::updatePosition()
{
    // kill orthogonal velocity to aviod sliding
    killOrthogonalVelocity(mLeftWheel);
    killOrthogonalVelocity(mRightWheel);
    killOrthogonalVelocity(mLeftRearWheel);
    killOrthogonalVelocity(mRightRearWheel);

    // compute acceleration and steering forces
    computeUndergroundImpact();

    computeDriving();
    computeSteering();
}

// x, y in pixels
void Car::startPosition(int x, int y, double angle)
{
    mBody->SetTransform(b2Vec2((double)x / PX_TO_M_RATIO, (double)y / PX_TO_M_RATIO), angle);
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
	if (impulse.Length() > MAX_LATERAL_IMPULSE)
		impulse *= MAX_LATERAL_IMPULSE / impulse.Length();

	//! Apply the linear impulse to each bodys center
	targetBody->ApplyLinearImpulseToCenter(impulse,true);
	//! Cancel the angular impulse by computing it through "Trägheitsmoment" * "Winkelgeschwindigkeit"
	//! 0.1f through trial and error
	targetBody->ApplyAngularImpulse(0.1f * targetBody->GetInertia() * -targetBody->GetAngularVelocity(), true);
}

void Car::computeDriving(){
	//! Driving
    mLeftWheel->ApplyForceToCenter(mEngineSpeed * mLeftWheel->GetWorldVector(b2Vec2(0,1)),true);
    mRightWheel->ApplyForceToCenter(mEngineSpeed * mRightWheel->GetWorldVector(b2Vec2(0,1)),true);
}

void Car::computeSteering(){
	//! Set motor speed of both revolute joints in relation to desired steering angle
    mSpeed = mSteeringAngle - mLeftJoint->GetJointAngle();
    mLeftJoint->SetMotorSpeed(mSpeed * STEER_SPEED);
    mSpeed = mSteeringAngle - mRightJoint->GetJointAngle();
    mRightJoint->SetMotorSpeed(mSpeed * STEER_SPEED);
}



