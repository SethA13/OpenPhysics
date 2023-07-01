#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include "../objects/definitions/GLFWobject.hpp"

#include "../../dependancies/glm/glm/glm.hpp"
#include "../../dependancies/glm/glm/gtx/string_cast.hpp"




/****************
 * PROTOTYPES
****************/
// collision detection
void handleCollision(GLFWobject &object1, GLFWobject &object2, bool DEBUG);

// circle formulas
void circleToCircleCollision(GLFWobject &circle1, GLFWobject &circle2, bool DEBUG);
void circleToRectangleCollision(GLFWobject &circle, GLFWobject &rectangle, bool DEBUG);
void circleToPointCollision(GLFWobject &circle, GLFWobject &point, bool DEBUG);

// rectangle formulas
void rectangleToRectangleCollision(GLFWobject &rectangle1, GLFWobject &rectangle2, bool DEBUG);
void rectangleToPointCollision(GLFWobject &rectangle, GLFWobject &point, bool DEBUG);

// point formula
void pointToPointCollision(GLFWobject &point1, GLFWobject &point2, bool DEBUG);

// sat Theorem for collisions not between these 3
void satTheorem(GLFWobject &object1, GLFWobject &object2, bool DEBUG);

void checkWindowBounds(GLFWobject &object, bool DEBUG);



// check if two objects are colliding
// TODO: find more elegant solution than if statements
void  handleCollision(GLFWobject &object1, GLFWobject &object2, bool DEBUG)
{
    // Check circle cases
    if ((object1.getShape() == 'c' && object2.getShape() == 'c') || (object1.getShape() == 'C' && object2.getShape() == 'C'))
    {
        if (DEBUG == TRUE)
        {
            std::cout << "Circle - Circle check..." << std::endl;
        }
        circleToCircleCollision(object1, object2, DEBUG);
        return;
    }
    else if ((object1.getShape() == 'c' && object2.getShape() == 'r') || ((object1.getShape() == 'r') && object2.getShape() == 'c'))
    {
        DEBUG = TRUE;
        if (DEBUG == TRUE)
        {
            std::cout << "Circle - Rectangle check..." << std::endl;
        }
        if (object1.getShape() == 'c')
        {
            if (DEBUG == TRUE)
            {
                std::cout << "Object 1 Circle..." << std::endl;
            }
            circleToRectangleCollision(object1, object2, DEBUG);
        }
        else
        {
            if (DEBUG == TRUE)
            {
                std::cout << "Object 2 Circle..." << std::endl;
            }
                
            circleToRectangleCollision(object2, object1, DEBUG);
        }
            
        
        return;
    }
    else if ((object1.getShape() == 'c' && object2.getShape() == 'p') || ((object1.getShape() == 'p') && object2.getShape() == 'c'))
    {
        if (DEBUG == TRUE)
        {
            std::cout << "Circle - Point check...!" << std::endl;
        }
        if (object1.getShape() == 'c')
        {
            circleToPointCollision(object1, object2, DEBUG);
        }
        else
            circleToPointCollision(object2, object1, DEBUG);
        return;
    }

    // Check rectangle cases
    else if ((object1.getShape() == 'r' && object2.getShape() == 'r'))
    {
        if (DEBUG == TRUE)
        {
            std::cout << "Rectangle - Rectangle check..." << std::endl;
        }
        rectangleToRectangleCollision(object1, object2, DEBUG);
        return;
    }
    else if ((object1.getShape() == 'r' && object2.getShape() == 'p') || ((object1.getShape() == 'p') && object2.getShape() == 'r'))
    {   
        if (DEBUG == TRUE)
        {
            std::cout << "Rectangle - Point check..." << std::endl;
        }
            
        if (object1.getShape() == 'r')
        {
            rectangleToPointCollision(object1, object2, DEBUG);
        }
        else
            rectangleToPointCollision(object2, object1, DEBUG);
        return;
    }

    // Check point case
    else if ((object1.getShape() == 'p' && object2.getShape() == 'p'))
    {
        if (DEBUG == TRUE)
        {
            std::cout << "Point - Point check..." << std::endl;
        }
            
        pointToPointCollision(object1, object2, DEBUG);
        return;
    }

    // Handle extraneous case
    else
    {
        satTheorem(object1, object2, DEBUG);
        return;
    }
}


/*******************************
 * Handle collision types
 * These are hardcoded types
*******************************/
void circleToCircleCollision(GLFWobject &circle1, GLFWobject &circle2, bool DEBUG)
{
    // Calculate distance between the centers of the circles
    glm::vec2 center1 = circle1.getPosition();
    glm::vec2 center2 = circle2.getPosition();
    float distance = glm::distance(center1, center2);

    // Check for collision
    if (distance <= circle1.getSize() + circle2.getSize())
    {
        // Circles have collided
        //std::cout << "Circle - Circle collision!" << std::endl;

        // Reverse the direction of both circles
        glm::vec2 newVelocity1 = -circle1.getVelocity();
        glm::vec2 newVelocity2 = -circle2.getVelocity();
        circle1.setVelocity(newVelocity1);
        circle2.setVelocity(newVelocity2);
    }
}

void circleToRectangleCollision(GLFWobject &circle, GLFWobject &rectangle, bool DEBUG)
{
    // Initial testing positions
    float testXSide = circle.getXPosition();
    float testYSide = circle.getYPosition();

    // Test for closest side

    // Left edge
    if (circle.getXPosition() < rectangle.getXPosition())
    {
        testXSide = rectangle.getXPosition();
    }
    // Right edge
    else if (circle.getXPosition() > rectangle.getXPosition() + rectangle.getWidth())
    {
        testXSide = rectangle.getXPosition() + rectangle.getWidth();
    }

    // Top edge
    if (circle.getYPosition() < rectangle.getYPosition())
    {
        testYSide = rectangle.getYPosition();
    }
    // Bottom edge
    else if (circle.getYPosition() > rectangle.getYPosition() + rectangle.getHeight())
    {
        testYSide = rectangle.getYPosition() + rectangle.getHeight();
    }

    float xDistance = testXSide - circle.getXPosition();
    float yDistance = testYSide - circle.getYPosition();
    float distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));
    
    if (distance <= circle.getSize())
    {
        // TODO handle collision

        // for now print that it collided for testing purposes
        if (DEBUG == TRUE)
        {
            std::cout << "Circle - Rectangle collision!" << std::endl;
        }
        rectangle.setVelocity(- rectangle.getVelocity());
        circle.setVelocity(- circle.getVelocity());
    }
    
    return;
}

void circleToPointCollision(GLFWobject &circle, GLFWobject &point, bool DEBUG)
{
    return;
}

void rectangleToRectangleCollision(GLFWobject &rectangle1, GLFWobject &rectangle2, bool DEBUG)
{
    return;
}

void rectangleToPointCollision(GLFWobject &rectangle, GLFWobject &point, bool DEBUG)
{
    return;
}

void pointToPointCollision(GLFWobject &point1, GLFWobject &point2, bool DEBUG)
{
    return;
}
/******************************
******************************/

void satTheorem(GLFWobject &object1, GLFWobject &object2, bool DEBUG)
{
    return;
}

void checkWindowBounds(GLFWobject &object, bool DEBUG)
{
    glm::vec2 center = object.getPosition();

    // Circle bounds check
    // Check left-most position
    if ((center[0]) + object.getSize() >= 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "left bounce" << std::endl;
        }
            
        object.setXVelocity((object.getXVelocity() * -1.0f));
    }
    // Check right-most position
    if ((center[0]) - object.getSize() <= -1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "right bounce" << std::endl;
        }
            
        object.setXVelocity((object.getXVelocity() * -1.0f));
    }

    // Check top-most position
    if ((center[1]) + object.getSize() >= 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "top bounce" << std::endl;
        }
            
        object.setYVelocity((object.getYVelocity() * -1.0f));
    }
    // Check bottom-most position
    if ((center[1]) - object.getSize() <= -1.0f) // At edge of window
    {
        // Change y direction
        if (DEBUG == TRUE)
        {
            std::cout << "bottom bounce" << std::endl;
        }
            
        object.setYVelocity((object.getYVelocity() * -1.0f));
    }
}

#endif // COLLISIONS_H