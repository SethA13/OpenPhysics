#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"object.h"

class Rectangle: public Object
{
private:
        char shape;
        float width;
        float height;
public:
    // getters
    char getShape();
    float getWidth();
    float getHeight();

    // setters
    char setShape();
    float setWidth();
    float setHeight();

    // constructor
    Rectangle(/* args */);

    // destructor
    ~Rectangle();
};

#endif //RECTANGLE_H