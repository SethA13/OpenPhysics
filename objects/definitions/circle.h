#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"

class Circle: public Object
{
private:
        char shape;
        float radius;
public:
    // getters
    char getShape();
    float getRadius();

    // setters
    char setShape();
    float setRadius();

    // constructors
    Circle(/* args */);
    ~Circle();
};

#endif // CIRCLE_H