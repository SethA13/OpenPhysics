#include "../definitions/rectangle.hpp"

/**********************
 * Constructors
**********************/
Rectangle::Rectangle(float width, float height, char shape)
    : Object(), width(width), height(height), shape(shape)
{
}

/********************
 * Getters
********************/
char Rectangle::getShape() const
{
    return shape;
}

float Rectangle::getWidth() const
{
    return width;
}

float Rectangle::getHeight() const
{
    return height;
}


/********************
 * Setters
********************/
void Rectangle::setShape(char shape)
{
    this->shape = shape;
}

void Rectangle::setWidth(float width)
{
    this->width = width;
}

void Rectangle::setHeight(float height)
{
    this->height = height;
}

/********************
 * Destructors
********************/
Rectangle::~Rectangle()
{
}