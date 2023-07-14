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
void handleCircleBoundary(GLFWobject &circle, bool DEBUG);
void handleRectangleBoundary(GLFWobject &point, bool DEBUG);
void handlePointBoundary(GLFWobject &point, bool DEBUG);

void moveHalfDistance(float halfdistance, GLFWobject &object);



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
    float distance = glm::distance((center1), (center2));

    // Check for collision
    if (distance <= circle1.getSize() + circle2.getSize())
    {
        // Circles have collided
        circle1.addCollision();
        circle2.addCollision();
        // Move each circle half the distance away from eachother
        moveHalfDistance((distance - circle1.getSize()) / 2.0f, circle1);
        moveHalfDistance((distance - circle2.getSize()) / 2.0f, circle2);
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
        circle.addCollision();
        rectangle.addCollision();
        // Reverse the direction of the circle
        float halfdistance = distance / 2.0f;
        glm::vec2 newVelocity = -circle.getVelocity();
        circle.setVelocity(newVelocity);
        newVelocity = -rectangle.getVelocity();
        rectangle.setVelocity(newVelocity);
    }
    return;
}

void circleToPointCollision(GLFWobject &circle, GLFWobject &point, bool DEBUG)
{

    // Calculate distance between the centers of the circles
    glm::vec2 center1 = circle.getPosition();
    glm::vec2 center2 = point.getPosition();
    float distance = glm::distance((center1), (center2));

    // Check for collision
    if (distance <= circle.getSize() + point.getSize())
    {
        // Circles have collided
        circle.addCollision();
        point.addCollision();
        // Move each circle half the distance away from eachother
        moveHalfDistance((distance - circle.getSize()) / 2.0f, circle);
        moveHalfDistance((distance - point.getSize()) / 2.0f, point);
        // Reverse the direction of both circles
        glm::vec2 newVelocity1 = -circle.getVelocity();
        glm::vec2 newVelocity2 = -point.getVelocity();
        circle.setVelocity(newVelocity1);
        point.setVelocity(newVelocity2);
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
        rectangle1.addCollision();
        rectangle2.addCollision();
        // Reverse the direction of both rectangles
        glm::vec2 newVelocity1 = -rectangle1.getVelocity();
        glm::vec2 newVelocity2 = -rectangle2.getVelocity();
        rectangle1.setVelocity(newVelocity1);
        rectangle2.setVelocity(newVelocity2);
    }
    return;
}

void rectangleToPointCollision(GLFWobject &rectangle, GLFWobject &point, bool DEBUG) //Programed the same as circle to rectangle collision to account for size
{
    // Calculate the closest point on the rectangle to the circle
    glm::vec2 rectPosition = rectangle.getPosition();
    glm::vec2 closestPoint;

    closestPoint.x = glm::clamp(point.getPosition().x, rectPosition.x - rectangle.getWidth() / 2.0f, rectPosition.x + rectangle.getWidth() / 2.0f);
    closestPoint.y = glm::clamp(point.getPosition().y, rectPosition.y - rectangle.getHeight() / 2.0f, rectPosition.y + rectangle.getHeight() / 2.0f);

    // Check if the closest point is within the circle
    float distance = glm::distance(point.getPosition(), closestPoint);
    if (distance <= point.getSize())
    {
        // Circle and rectangle have collided
        point.addCollision();
        rectangle.addCollision();
        // Reverse the direction of the circle
        float halfdistance = distance / 2.0f;
        glm::vec2 newVelocity = -point.getVelocity();
        point.setVelocity(newVelocity);
        newVelocity = -rectangle.getVelocity();
        rectangle.setVelocity(newVelocity);
    }
    return;
}

void pointToPointCollision(GLFWobject &point1, GLFWobject &point2, bool DEBUG) //Programed as two circles to account for the size change for vision
{
    // Calculate distance between the centers of the circles
    glm::vec2 center1 = point1.getPosition();
    glm::vec2 center2 = point2.getPosition();
    float distance = glm::distance((center1), (center2));

    // Check for collision
    if (distance <= point1.getSize() + point2.getSize())
    {
        // Circles have collided
        point1.addCollision();
        point2.addCollision();
        // Move each circle half the distance away from eachother
        moveHalfDistance((distance - point1.getSize()) / 2.0f, point1);
        moveHalfDistance((distance - point2.getSize()) / 2.0f, point2);
        // Reverse the direction of both circles
        glm::vec2 newVelocity1 = -point1.getVelocity();
        glm::vec2 newVelocity2 = -point2.getVelocity();
        point1.setVelocity(newVelocity1);
        point2.setVelocity(newVelocity2);
    }
}
/******************************
******************************/

void satTheorem(GLFWobject &object1, GLFWobject &object2, bool DEBUG)
{
    return;
}

void checkWindowBounds(GLFWobject &object, bool DEBUG)
{
    if (object.getShape() == 'c')
    {
        handleCircleBoundary(object, DEBUG);
    }
    else if (object.getShape() == 'r')
    {
        handleRectangleBoundary(object, DEBUG);
    }
    else if (object.getShape() == 'p')
    {
        handlePointBoundary(object, DEBUG);
    }
}

void handleCircleBoundary(GLFWobject &circle, bool DEBUG)
{
    glm::vec2 center = circle.getPosition();
    // Check right-most position
    if ((center[0]) + circle.getSize() > 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "left bounce" << std::endl;
        }
            
        circle.setXVelocity((circle.getXVelocity() * -1.0f));
    }
    // Check left-most position
    if ((center[0]) - circle.getSize() < -1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "right bounce" << std::endl;
        }
            
        circle.setXVelocity((circle.getXVelocity() * -1.0f));
    }

    // Check top-most position
    if ((center[1]) + circle.getSize() > 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "top bounce" << std::endl;
        }
            
        circle.setYVelocity((circle.getYVelocity() * -1.0f));
    }
    // Check bottom-most position
    if ((center[1]) - circle.getSize() < -1.0f) // At edge of window
    {
        // Change y direction
        if (DEBUG == TRUE)
        {
            std::cout << "bottom bounce" << std::endl;
        }
            
        circle.setYVelocity((circle.getYVelocity() * -0.9f));
    }
    return;
}

void handleRectangleBoundary(GLFWobject &rectangle, bool DEBUG)
{
    glm::vec2 center = rectangle.getPosition();
    // Check right-most position
    if ((center[0]) + (rectangle.getWidth() / 2) > 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "left bounce" << std::endl;
        }
            
        rectangle.setXVelocity((rectangle.getXVelocity() * -1.0f));
    }
    // Check left-most position
    if ((center[0]) - (rectangle.getWidth() / 2) < -1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "right bounce" << std::endl;
        }
            
        rectangle.setXVelocity((rectangle.getXVelocity() * -1.0f));
    }

    // Check top-most position
    if ((center[1]) + (rectangle.getHeight() / 2) > 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "top bounce" << std::endl;
        }
            
        rectangle.setYVelocity((rectangle.getYVelocity() * -1.0f));
    }
    // Check bottom-most position
    if ((center[1]) - (rectangle.getHeight() / 2) < -1.0f) // At edge of window
    {
        // Change y direction
        if (DEBUG == TRUE)
        {
            std::cout << "bottom bounce" << std::endl;
        }
            
        rectangle.setYVelocity((rectangle.getYVelocity() * -0.9f));
    }
    return;
}

void handlePointBoundary(GLFWobject &point, bool DEBUG)
{
    glm::vec2 center = point.getPosition();
    // Check right-most position
    if ((center[0]) > 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "left bounce" << std::endl;
        }
            
        point.setXVelocity((point.getXVelocity() * -1.0f));
    }
    // Check left-most position
    if ((center[0]) < -1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "right bounce" << std::endl;
        }
            
        point.setXVelocity((point.getXVelocity() * -1.0f));
    }

    // Check top-most position
    if ((center[1]) > 1.0f) // At edge of window
    {
        // Change x direction
        if (DEBUG == TRUE)
        {
            std::cout << "top bounce" << std::endl;
        }
            
        point.setYVelocity((point.getYVelocity() * -1.0f));
    }
    // Check bottom-most position
    if ((center[1]) < -1.0f) // At edge of window
    {
        // Change y direction
        if (DEBUG == TRUE)
        {
            std::cout << "bottom bounce" << std::endl;
        }
            
        point.setYVelocity((point.getYVelocity() * -0.9f));
    }
    return;
}

void moveHalfDistance(float halfdistance, GLFWobject &object)
{
    object.setPosition(object.getPosition() + halfdistance);
    return;
}

#endif // COLLISIONS_H