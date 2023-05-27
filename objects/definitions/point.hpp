#ifndef POINT_H
#define POINT_H
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
    float getXPosition();
    float getYPosition();
    // setter
    float setXPosition();
    float setYPosition();
    // constructors

    Point(float xPosition, float yPosition) : xPosition(0.0), yPosition(0.0) {}

    // destructor
    ~Point();
};

#endif // POINT_H