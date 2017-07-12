#ifndef CAR_H
#define CAR_H

#include <QtCore/QtMath>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include "track.h"


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
    const int PX_TO_M_RATIO = 20;
    const float CAR_ROTATION_ANGLE = 0.0;//-90.0;

	//! Variable car properties
	//! max steering lock angle (default at pi/3)
    const float MAX_STEER_ANGLE = (float)M_PI/7.0f;
    const float STEER_SPEED = 5.0f;//1.5f;         //5.0f;
    const float HORSEPOWERS = 8000.0f;       //240.0f;
    const float MAX_LATERAL_IMPULSE = 0.0f; //1.7f; //! for drifting :D
    const float MAX_TORQUE = 100.0f; //100.0f
    //const b2Vec2 CAR_STARTING_POS = b2Vec2(0.0f,0.0f);


    // car constants
    const float CAR_LENGTH = 4.4f;
    const float CAR_WIDTH = 2.0f;       // Total Car Weight
    const float CAR_WEIGHT = 650.0f;
    const float TYRE_LENGTH = 0.5f;
    const float TYRE_WIDTH = 0.245f;
    const float TYRE_WEIGHT = 9.0f;

    const b2Vec2 mLeftRearWheelPosition  = b2Vec2(-(CAR_WIDTH/2.0f),((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));
    const b2Vec2 mRightRearWheelPosition = b2Vec2((CAR_WIDTH/2.0f),((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));
    const b2Vec2 mLeftFrontWheelPosition = b2Vec2(-(CAR_WIDTH/2.0f),-((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));
    const b2Vec2 mRightFrontWheelPosition = b2Vec2((CAR_WIDTH/2.0f),-((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));

	//! Define the User Input States
    enum InputState mInput;
	//! Variables for user input
	float mEngineSpeed =0.0f;
	float mSteeringAngle = 0.0f;
	float mSpeed;

    b2Vec2 mCarPosition = b2Vec2(110.0f, 50.0f);

	//! b2World Objects
    b2World *mWorld;
	b2Body *mBody;

    b2Body *mRightWheel;
    b2Body *mLeftWheel;
    b2Body *mRightRearWheel;
    b2Body *mLeftRearWheel;

    b2RevoluteJoint *mRightJoint;
    b2RevoluteJoint *mLeftJoint;
    b2PrismaticJoint *mRightRearJoint;
    b2PrismaticJoint *mLeftRearJoint;

    Track* mTrack;

signals:
    void playCarSound();
    void stopCarSound();

public:
	//! Fill the world with car object constructor
    Car(b2World* world, Track* track);
    ~Car();
	//! Show the car on screen
	void render();
	//! Let wheels only roll "forward"
    void killOrthogonalVelocity(b2Body* targetBody);
	//! Compute the driving force
	void computeDriving();
	//! Compute the joint motor torque
	void computeSteering();
	//! Compute events on which key pressed
    void computeUserInput(enum InputState input);

    void computeUndergroundImpact();

    void updatePosition();
    void setPosition(int x, int y, double angle);
    void setPosition(WorldPosition position);
};

#endif // CAR_H
