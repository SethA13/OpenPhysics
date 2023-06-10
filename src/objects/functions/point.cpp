#include "../definitions/point.hpp"

/**********************
 * Constructors
**********************/
Point::Point(float xPosition, float yPosition)
    : xPosition(xPosition), yPosition(yPosition)
{
}

/********************
 * Getters
********************/
float Point::getXPosition() const
{
    return xPosition;
}

float Point::getYPosition() const
{
    return yPosition;
}

/********************
 * Setters
********************/
void Point::setXPosition(float x)
{
    xPosition = x;
}

void Point::setYPosition(float y)
{
    yPosition = y;
}

/********************
 * Destructors
********************/
Point::~Point()
{
}
