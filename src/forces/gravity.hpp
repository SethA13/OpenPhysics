#ifndef GRAVITY_H
#define GRAVITY_H

#include <GLFW/glfw3.h>

// Abstract base class for objects affected by gravity
class GravityObject {
public:
    virtual void applyGravity(float deltaTime) = 0;
};

// Gravity class that applies gravity to a GravityObject
class Gravity {
public:
    Gravity(GravityObject& object, float gravity)
        : object(object), gravity(gravity), velocity(0.0f)
    {
    }

    void applyGravity(float deltaTime)
    {
        // Calculate the new position based on velocity and gravity
        velocity += gravity * deltaTime;
        object.applyGravity(velocity);
    }

private:
    GravityObject& object;
    float gravity;
    float velocity;
};

#endif  // GRAVITY_H
