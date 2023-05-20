#ifndef OBJECT_H
#define OBJECT_H
/**********************************************
 * OBJECT
 * The base class that all shapes inherit from.  
 **********************************************/
class object
{
private:
    float radius;
    char objectShape;

public:
    // getter
    float getRadius();
    char getShape();
    // setter
    float setRadius();
    char setShape();
    // constructors

    object(float radius, char objectShape) : radius(0.0), objectShape('n') {}

    // destructor
    ~object();
};

#endif // OBJECT_H