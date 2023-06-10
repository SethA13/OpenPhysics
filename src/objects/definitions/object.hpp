#ifndef OBJECT_H
#define OBJECT_H

#include "point.hpp"
#include "velocity.hpp"
/**********************************************
 * OBJECT
 * The base class that all shapes inherit from.  
 **********************************************/
class Object
{
private:
    Point centerPoint;
    Velocity velocity;
    float rotation;

public:
    // getter
    Point getCenterPoint() const;
    Velocity getVelocity() const;
    float getRotation() const;
    // setter
    void setCenterPoint(const Point& center);
    void setVelocity(const Velocity& v);
    void setRotation(float angle);
    // constructors

    Object(const Point& centerPoint = Point(0.0, 0.0), const Velocity& velocity = Velocity(0.0, 0.0), float rotation = 0.0);


    // destructor
    virtual ~Object();
};

#endif // OBJECT_H