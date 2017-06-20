#ifndef CAR_H
#define CAR_H

#include <QtCore/QtMath>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QObject>


enum InputState
{
    None = 0,
    Accelerate,
    AccelerateSteerRight,
    AccelerateSteerLeft,
    Break,
    BreakSteerRight,
    BreakSteerLeft,
    SteerRight,
    SteerLeft
};


class Car : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
private:
	//! Set the relation of display pixels and meters
	const int PX_TO_M_RATIO = 10;
	const float CAR_ROTATION_ANGLE = -90.0;

	//! Variable car properties
	//! max steering lock angle (default at pi/3)
	const float MAX_STEER_ANGLE = (float)M_PI/3.0f;
	const float STEER_SPEED = 5.0f;
	const float HORSEPOWERS = 240.0f;
	const float MAX_LATERAL_IMPULSE = 1.7f; //! for drifting :D
	const b2Vec2 CAR_STARTING_POS = b2Vec2(30,30);

	const b2Vec2 leftRearWheelPosition  = b2Vec2(-1.5f,1.9f);
	const b2Vec2 rightRearWheelPosition = b2Vec2(1.5f,1.9f);
	const b2Vec2 leftFrontWheelPosition = b2Vec2(-1.5f,-1.9f);
	const b2Vec2 rightFrontWheelPosition = b2Vec2(1.5f,-1.9f);

	//! Define the User Input States
    enum InputState input;
	//! Variables for user input
	float mEngineSpeed =0.0f;
	float mSteeringAngle = 0.0f;
	float mSpeed;

	//! b2World Objects
	b2World *mWorld;
	b2Body *mBody;

	b2Body *rightWheel;
	b2Body *leftWheel;
	b2Body *rightRearWheel;
	b2Body *leftRearWheel;

	b2RevoluteJoint *rightJoint;
	b2RevoluteJoint *leftJoint;

public:
	//! Fill the world with car object constructor
	Car(b2World* mWorld);
	//! Show the car on screen
	void render();
	//! Let wheels only roll "forward"
	void killOrthogonalVelocity(b2Body*);
	//! Compute the driving force
	void computeDriving();
	//! Compute the joint motor torque
	void computeSteering();
	//! Compute events on which key pressed
	void computeUserInput(enum InputState input);

	//Returns the wheel bodys for world loop
	b2Body *GetLeftWheel();
	b2Body *GetLeftRearWheel();
	b2Body *GetRightWheel();
	b2Body *GetRightRearWheel();
};

#endif // CAR_H
