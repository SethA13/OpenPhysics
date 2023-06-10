#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"object.hpp"

class Rectangle: public Object
{
private:
    GLint numSegments;
    std::vector<GLfloat> circleVertices;
        char shape;
        float width;
        float height;
public:
    // getters
    char getShape() const;
    float getWidth() const;
    float getHeight() const;
    const std::vector<GLfloat>& getVertices() const
    {
        return circleVertices;
    }


    // setters
    void setShape(char shape);
    void setWidth(float width);
    void setHeight(float height);

    // constructor
    Rectangle(float width = 0.0, float height = 0.0, char shape = ' ');

    // destructor
    ~Rectangle();
};

#endif //RECTANGLE_H