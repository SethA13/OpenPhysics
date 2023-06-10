#include "../definitions/object.hpp"

/**********************
 * Constructors
**********************/
Object::Object(const Point& centerPoint, const Velocity& velocity, float rotation)
    : centerPoint(centerPoint), velocity(velocity), rotation(rotation)
{
}

/********************
 * Getters
********************/
Point Object::getCenterPoint() const
{
    return centerPoint;
}

Velocity Object::getVelocity() const
{
    return velocity;
}

float Object::getRotation() const
{
    return rotation;
}

/********************
 * Setters
********************/
void Object::setCenterPoint(const Point& center)
{
    centerPoint = center;
}

void Object::setVelocity(const Velocity& v)
{
    velocity = v;
}

void Object::setRotation(float angle)
{
    rotation = angle;
}

/********************
 * Destructors
********************/
Object::~Object()
{
}