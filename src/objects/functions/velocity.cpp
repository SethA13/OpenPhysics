#include "../definitions/velocity.hpp"

// Constructors
Velocity::Velocity(float deltaX, float deltaY)
    : deltaX(deltaX), deltaY(deltaY)
{
}

// Getters
float Velocity::getDeltaX() const
{
    return deltaX;
}

float Velocity::getDeltaY() const
{
    return deltaY;
}

// Setters
void Velocity::setDeltaX(float value)
{
    deltaX = value;
}

void Velocity::setDeltaY(float value)
{
    deltaY = value;
}

// Destructor
Velocity::~Velocity()
{
}