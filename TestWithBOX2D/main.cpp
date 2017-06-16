#include <QCoreApplication>
#include <Box2D.h>
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    for (int32 i = 0; i < 60; ++i)
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);

        // Now print the position and angle of the body.
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

    getchar();

    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.

    return a.exec();
}


/*  //!Create world
    b2World *world = new b2World(b2Vec2(0.0f,9.81f));

    b2Body *dynamicBody, *staticBody, *kinematicBody;
    b2BodyDef myBodyDef;
    b2PolygonShape polygon;
    b2FixtureDef fixture;

    //! Define shape of bodys as 1x1 Box
    polygon.SetAsBox(1,1);

    //!Create fixture
    fixture.shape = &polygon;
    fixture.density = 1;
    //!Define body type
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(100,100);
    dynamicBody = world->CreateBody(&myBodyDef);
    dynamicBody->CreateFixture(&fixture);

    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(20,10);
    staticBody = world->CreateBody(&myBodyDef);
    staticBody->CreateFixture(&fixture);

    myBodyDef.type = b2_kinematicBody;
    myBodyDef.position.Set(30,10);
    kinematicBody = world->CreateBody(&myBodyDef);
    kinematicBody->CreateFixture(&fixture);



    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    for (int32 i = 0; i < 60; ++i)
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world->Step(timeStep, velocityIterations, positionIterations);

        b2Vec2 pos = dynamicBody->GetPosition();
        float angle = dynamicBody->GetAngle();
        b2Vec2 vel = dynamicBody->GetLinearVelocity();
        float angularVel = dynamicBody->GetAngularVelocity();

    std::cout << pos.x, pos.y,   vel.x, vel.y,    angle, angularVel;

    }
getchar();

    return a.exec();
}*/
