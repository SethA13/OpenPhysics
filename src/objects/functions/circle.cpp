#include "../definitions/circle.hpp"

/**********************
 * Constructors
**********************/
Circle::Circle(float radius, char shape)
    : Object(), radius(radius), shape(shape)
{
}

/********************
 * Getters
********************/
char Circle::getShape() const
{
    return shape;
}

float Circle::getRadius() const
{
    return radius;
}

/********************
 * Setters
********************/
void Circle::setShape(char shape)
{
    this->shape = shape;
}

void Circle::setRadius(float radius)
{
    this->radius = radius;
}

/********************
 * Destructors
********************/
Circle::~Circle()
{
}