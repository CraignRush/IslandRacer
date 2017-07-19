#ifndef CAR_H
#define CAR_H

#include <Box2D/Box2D.h>
#include <QtCore/QtMath>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include <QDebug>
#include <QMetaObject>
#include <cmath>
#include <time.h>
#include "worldposition.h"
#include "track.h"
#include "sound.h"

//! This enum contains all posible car movments
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


//! Creates a car with interact methods
class Car : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

private:
    // Set the relation of display pixels and meters
    const int PX_TO_M_RATIO = 20;
    const float CAR_ROTATION_ANGLE = 0.0;//-90.0;

    // Variable car properties
    // max steering lock angle (default at pi/3)
    const float MAX_STEER_ANGLE = (float)M_PI/4.0f;
    const float STEER_SPEED = 5.0f;//1.5f;         //5.0f;
    const float HORSEPOWERS = 3500.0f;       //240.0f;
    const float MAX_LATERAL_IMPULSE = 20.0f; //1.7f; // for drifting :D
    const float MAX_TORQUE = 100.0f; //100.0f
    //const b2Vec2 CAR_STARTING_POS = b2Vec2(0.0f,0.0f);


    // car constants (in mks system)
    const float CAR_LENGTH = 4.4f;
	const float CAR_WIDTH = 2.0f;
	const float CAR_WEIGHT = 550.0f; // Total Car Weight
    const float TYRE_LENGTH = 0.5f;
    const float TYRE_WIDTH = 0.245f;
    const float TYRE_WEIGHT = 9.0f;

    const b2Vec2 mLeftRearWheelPosition  = b2Vec2(-(CAR_WIDTH/2.0f),((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));
    const b2Vec2 mRightRearWheelPosition = b2Vec2((CAR_WIDTH/2.0f),((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));
    const b2Vec2 mLeftFrontWheelPosition = b2Vec2(-(CAR_WIDTH/2.0f),-((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));
    const b2Vec2 mRightFrontWheelPosition = b2Vec2((CAR_WIDTH/2.0f),-((CAR_LENGTH/2.0f) - (TYRE_LENGTH/2.0f) - 0.15f));

    //Factors you select in the garage
    double mSpeedFac;
    double mAccelerationFac;
    double mHandlingFac;

    // Define the User Input States
    enum InputState mInput;
    // Variables for user input
	float mEngineSpeed =0.0f;
	float mSteeringAngle = 0.0f;
	float mSpeed;

    b2Vec2 mCarPosition = b2Vec2(110.0f, 50.0f);
    int mIndex;

    // b2World Objects
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
    //! Signal to start car sound
    void playCarSound();

    //! Signal to start water sound
    void playWaterSound();

    //! Signal to start the underwater effect if user drove into water
    void startUnderwaterEffect(int index);

    //! Signal to stop car sound
    void stopCarSound();

public:
    //! Fill the world with car object
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

    //! Compute angular velocity for swirl animation
    void computeSwirl();

    //! Compute events on which key pressed
    void computeUserInput(enum InputState input);

    //! Compute the different impact to the car
    /*! \param index Number of player (1 or 2)
     */
    void computeUndergroundImpact(int index);

    //! New car position for each time step is calculated
    /*! \param index Number of player (1 or 2)
     *! \param underwaterAnimationActive underwater effect running state
     */
    void updatePosition(int index, bool underwaterAnimationActive);

    //! New car is created and set to position
    /*!
     * \param x x-coordinate
     * \param y y-coordinate
     * \param angle rotation angle
     */
    void setPosition(int x, int y, double angle);

    //! Set car to position
    void setPosition(WorldPosition position);

    //! Calculate parameter with "garage" values that impact car values
    /*!
     * \param speedValue Garage value for topspeed
     * \param accelerationValue Garage value for acceleration
     * \param handlingValue Garage value for handling
     */
    void setCarParams(int speedValue, int accelerationValue, int handlingValue);

public slots:

    void setToResetPos();

    void setCarPixmap(int carIndex);
};

#endif // CAR_H
