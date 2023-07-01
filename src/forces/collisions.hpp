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
    if (DEBUG == TRUE)
    {
        std::cout << "Object 1; " << object1.getShape() << std::endl;
        std::cout << "Object 2; " << object2.getShape() << std::endl;
    }
    
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
        // Reverse the direction of both circles
        glm::vec2 newVelocity1 = -circle1.getVelocity();
        glm::vec2 newVelocity2 = -circle2.getVelocity();
        circle1.setVelocity(newVelocity1);
        circle2.setVelocity(newVelocity2);
    }
}

void circleToRectangleCollision(GLFWobject &circle, GLFWobject &rectangle, bool DEBUG)
{
    // Calculate the closest point on the rectangle to the circle
    glm::vec2 rectPosition = rectangle.getPosition();
    glm::vec2 closestPoint;

    closestPoint.x = glm::clamp(circle.getPosition().x, rectPosition.x - rectangle.getWidth() / 2.0f, rectPosition.x + rectangle.getWidth() / 2.0f);
    closestPoint.y = glm::clamp(circle.getPosition().y, rectPosition.y - rectangle.getHeight() / 2.0f, rectPosition.y + rectangle.getHeight() / 2.0f);

    // Check if the closest point is within the circle
    float distance = glm::distance(circle.getPosition(), closestPoint);
    if (distance <= circle.getSize())
    {
        // Circle and rectangle have collided
        // Reverse the direction of the circle
        glm::vec2 newVelocity = -circle.getVelocity();
        circle.setVelocity(newVelocity);
        newVelocity = -rectangle.getVelocity();
        rectangle.setVelocity(newVelocity);
    }
    return;
}

void circleToPointCollision(GLFWobject &circle, GLFWobject &point, bool DEBUG)
{
    DEBUG = TRUE;

    float distance = glm::distance(circle.getPosition(), point.getPosition());
    if (distance <= circle.getSize())
    {
        if (DEBUG == TRUE)
        {
            std::cout << "Circle - Point Collision!" << std::endl;
        }
        circle.setXVelocity(- circle.getXVelocity());
        point.setXVelocity(- point.getXVelocity());
        circle.setYVelocity(- circle.getYVelocity());
        point.setYVelocity(- point.getYVelocity());
    }

    
    return;
}

void rectangleToRectangleCollision(GLFWobject &rectangle1, GLFWobject &rectangle2, bool DEBUG)
{
    // Calculate the AABB (Axis-Aligned Bounding Box) for each rectangle
    glm::vec2 rect1Position = rectangle1.getPosition();
    glm::vec2 rect2Position = rectangle2.getPosition();
    float rect1Left = rect1Position.x - rectangle1.getWidth() / 2.0f;
    float rect1Right = rect1Position.x + rectangle1.getWidth() / 2.0f;
    float rect1Top = rect1Position.y + rectangle1.getHeight() / 2.0f;
    float rect1Bottom = rect1Position.y - rectangle1.getHeight() / 2.0f;

    float rect2Left = rect2Position.x - rectangle2.getWidth() / 2.0f;
    float rect2Right = rect2Position.x + rectangle2.getWidth() / 2.0f;
    float rect2Top = rect2Position.y + rectangle2.getHeight() / 2.0f;
    float rect2Bottom = rect2Position.y - rectangle2.getHeight() / 2.0f;

    // Check for overlap in the x-axis and y-axis
    if (rect1Left <= rect2Right && rect1Right >= rect2Left && rect1Top >= rect2Bottom && rect1Bottom <= rect2Top)
    {
        // Rectangles have collided
        // Reverse the direction of both rectangles
        glm::vec2 newVelocity1 = -rectangle1.getVelocity();
        glm::vec2 newVelocity2 = -rectangle2.getVelocity();
        rectangle1.setVelocity(newVelocity1);
        rectangle2.setVelocity(newVelocity2);
    }
    return;
}

void rectangleToPointCollision(GLFWobject &rectangle, GLFWobject &point, bool DEBUG)
{
    // Calculate the AABB (Axis-Aligned Bounding Box) for the rectangle
    glm::vec2 rectPosition = rectangle.getPosition();
    float rectLeft = rectPosition.x - rectangle.getWidth() / 2.0f;
    float rectRight = rectPosition.x + rectangle.getWidth() / 2.0f;
    float rectTop = rectPosition.y + rectangle.getHeight() / 2.0f;
    float rectBottom = rectPosition.y - rectangle.getHeight() / 2.0f;

    // Check if the point is within the rectangle
    glm::vec2 pointPosition = point.getPosition();
    if (pointPosition.x >= rectLeft && pointPosition.x <= rectRight && pointPosition.y >= rectBottom && pointPosition.y <= rectTop)
    {
        // Point is inside the rectangle
        // Reverse the direction of both the rectangle and the point
        glm::vec2 newVelocity1 = -rectangle.getVelocity();
        glm::vec2 newVelocity2 = -point.getVelocity();
        rectangle.setVelocity(newVelocity1);
        point.setVelocity(newVelocity2);
    }
    return;
}

void pointToPointCollision(GLFWobject &point1, GLFWobject &point2, bool DEBUG)
{
    if (point1.getPosition() == point2.getPosition())
    {
        point1.setVelocity(- point1.getVelocity());
        point2.setVelocity(- point2.getVelocity());
    }
    
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


/**********
 * float circleXDistance = abs(circle.getXPosition() - rectangle.getXPosition());
    float circleYDistance = abs(circle.getYPosition() - rectangle.getYPosition());
    float cornerDistance = (((circleXDistance - rectangle.getWidth() / 2) * (circleXDistance - rectangle.getWidth() / 2)) + ((circleYDistance - rectangle.getHeight() / 2) * (circleYDistance - rectangle.getHeight() / 2)));

    if ((circleXDistance <= (rectangle.getWidth() / 2)) || (circleYDistance <= (rectangle.getHeight() / 2)))
    {
        //TODO handle collision
    }
*/

#endif // COLLISIONS_H