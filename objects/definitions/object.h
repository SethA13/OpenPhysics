#ifndef OBJECT_H
#define OBJECT_H

#include "point.h"
/**********************************************
 * OBJECT
 * The base class that all shapes inherit from.  
 **********************************************/
class Object
{
private:
    Point centerPoint;

public:
    // getter
    Point getCenterPoint();
    // setter
    Point setCenterPoint();
    // constructors

    Object(Point centerPoint) : centerPoint(0.0, 0.0) {}

    // destructor
    ~Object();
};

#endif // OBJECT_H