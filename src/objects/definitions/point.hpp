#ifndef POINT_H
#define POINT_H

#include <iostream>
/************************************************
 * POINT
 * The base class that all shapes inherit from.
 * It contains the center location of the object.  
 ************************************************/
class Point
{
private:
    float xPosition;
    float yPosition;

public:
    // getter
    float getXPosition() const;
    float getYPosition() const;
    // setter
    void setXPosition(float x);
    void setYPosition(float y);


    // constructors
    Point(float xPosition, float yPosition);
    Point()            : xPosition(0.0), yPosition(0.0)  {}
    Point(bool check)  : xPosition(0.0), yPosition(0.0)  {}

    void addX(float dx);
    void addY(float dy);

    // destructor
    ~Point();
};

std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

#endif // POINT_H