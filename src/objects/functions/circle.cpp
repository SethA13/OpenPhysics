#include "../definitions/circle.hpp"

/**********************
 * Constructors
**********************/


/********************
 * Getters
********************/
char Circle::getShape()
{
    return this->shape;
}

float Circle::getRadius()
{
    return this->radius;
}

/********************
 * Setters
********************/
char Circle::setShape()
{
    shape = this->shape;
}

float Circle::setRadius()
{
    radius = this->radius;
}

/********************
 * Destructors
********************/