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
    float getXPosition() const;
    float getYPosition() const;
    // setter
    void setXPosition(float x);
    void setYPosition(float y);


    // constructors
    Point(float xPosition = 0.0, float yPosition = 0.0);

    // destructor
    ~Point();
};

#endif // POINT_H