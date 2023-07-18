#include "../definitions/point.hpp"

/**********************
 * Constructors
**********************/
Point::Point(float x, float y) : xPosition(0.0), yPosition(0.0)
{
   setXPosition(x);
   setYPosition(y);
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
    this->xPosition = x;
}

void Point::setYPosition(float y)
{
    this->yPosition = y;
}

/********************
 * Destructors
********************/
Point::~Point()
{
}

void Point::addX(float dx)
{
    setXPosition(getXPosition() + dx);
}

void Point::addY(float dy)
{
    setYPosition(getYPosition() + dy);
}