#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdio.h>
#include <vector>
#include "../objects/definitions/GLFWobject.hpp"

#include "../../dependancies/glm/glm/glm.hpp"
#include "../../dependancies/glm/glm/gtx/string_cast.hpp"


/****************
 * PROTOTYPES
****************/
// collision detection
void handleCollision(GLFWobject &object1, GLFWobject &object2);

// circle formulas
void circleToCircleCollision(GLFWobject &circle1, GLFWobject &circle2);
void circleToRectangleCollision(GLFWobject &circle, GLFWobject &rectangle);
void circleToPointCollision(GLFWobject &circle, GLFWobject &point);

// rectangle formulas
void rectangleToRectangleCollision(GLFWobject &rectangle1, GLFWobject &rectangle2);
void rectangleToPointCollision(GLFWobject &rectangle, GLFWobject &point);

// point formula
void pointToPointCollision(GLFWobject &point1, GLFWobject &point2);

// sat Theorem for collisions not between these 3
void satTheorem(GLFWobject &object1, GLFWobject &object2);

void checkWindowBounds(GLFWobject &object);



// check if two objects are colliding
// TODO: find more elegant solution than if statements
void  handleCollision(GLFWobject &object1, GLFWobject &object2)
{
    // Check circle cases
    if ((object1.getShape() == 'c') && object2.getShape() == 'c')
    {
        circleToCircleCollision(object1, object2);
        return;
    }
    else if (((object1.getShape() == 'c') && object2.getShape() == 'r') || ((object1.getShape() == 'r') && object2.getShape() == 'c'))
    {
        return;
    }
    else if (((object1.getShape() == 'c') && object2.getShape() == 'p') || ((object1.getShape() == 'p') && object2.getShape() == 'c'))
    {
        return;
    }

    // Check rectangle cases
    else if ((object1.getShape() == 'r') && object2.getShape() == 'r')
    {
        return;
    }
    else if (((object1.getShape() == 'r') && object2.getShape() == 'p') || ((object1.getShape() == 'p') && object2.getShape() == 'r'))
    {
        return;
    }

    // Check point case
    else if ((object1.getShape() == 'p') && object2.getShape() == 'p')
    {
        return;
    }

    // Handle extraneous case
    else
        return;
}


/*******************************
 * Handle collision types
 * These are hardcoded types
*******************************/
void circleToCircleCollision(GLFWobject &circle1, GLFWobject &circle2)
{
    // Calculate distance between the centers of the circles
    glm::vec2 center1 = circle1.getPosition();
    glm::vec2 center2 = circle2.getPosition();
    float distance = glm::distance(center1, center2);

    // Check for collision
    if (distance <= circle1.getSize() + circle2.getSize())
    {
        // Circles have collided
        std::cout << "Circle - Circle collision!" << std::endl;

        // Reverse the direction of both circles
        glm::vec2 newVelocity1 = -circle1.getVelocity();
        glm::vec2 newVelocity2 = -circle2.getVelocity();
        circle1.setVelocity(newVelocity1);
        circle2.setVelocity(newVelocity2);
    }
}

void circleToRectangleCollision(GLFWobject &circle, GLFWobject &rectangle)
{
    return;
}

void circleToPointCollision(GLFWobject &circle, GLFWobject &point)
{
    return;
}

void rectangleToRectangleCollision(GLFWobject &rectangle1, GLFWobject &rectangle2)
{
    return;
}

void rectangleToPointCollision(GLFWobject &rectangle, GLFWobject &point)
{
    return;
}

void pointToPointCollision(GLFWobject &point1, GLFWobject &point2)
{
    return;
}
/******************************
******************************/

void satTheorem(GLFWobject &object1, GLFWobject &object2)
{
    return;
}

void checkWindowBounds(GLFWobject &object)
{
    // std::cout << "Circle" << i + 1 << " Radius; " << object.getSize() << std::endl;
    glm::vec2 center = object.getPosition();

    // Circle bounds check
    // Check left-most position
    if ((center[0]) + object.getSize() >= 1.0f) // At edge of window
    {
        // Change x direction
        //std::cout << "left bounce" << std::endl;
        object.setXVelocity((object.getXVelocity() * -1.0f));
    }
    // Check right-most position
    if ((center[0]) - object.getSize() <= -1.0f) // At edge of window
    {
        // Change x direction
        //std::cout << "right bounce" << std::endl;
        object.setXVelocity((object.getXVelocity() * -1.0f));
    }

    // Check top-most position
    if ((center[1]) + object.getSize() >= 1.0f) // At edge of window
    {
        // Change x direction
        // std::cout << "top bounce" << std::endl;
        object.setYVelocity((object.getYVelocity() * -1.0f));
    }
    // Check bottom-most position
    if ((center[1]) - object.getSize() <= -1.0f) // At edge of window
    {
        // Change y direction
        // std::cout << "bottom bounce" << std::endl;
        // std::cout << "Circle"" bounce at " << glm::to_string(object.getPosition() + object.getSize()) << std::endl;
        object.setYVelocity((object.getYVelocity() * -1.0f));
    }
}

#endif // COLLISIONS_H