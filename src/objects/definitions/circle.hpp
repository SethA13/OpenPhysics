#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.hpp"

class Circle: public Object
{
private:
        char shape;
        float radius;
public:
    // getters
    char getShape() const;
    float getRadius() const;

    // setters
    void setShape(char shape);
    void setRadius(float radius);

    // constructor
    Circle(float radius = 0.0, char shape = 'C');

    // destructor
    ~Circle();
};

#endif // CIRCLE_H