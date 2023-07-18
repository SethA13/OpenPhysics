#ifndef GLFWOBJECT_H
#define GLFWOBJECT_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "../../../dependancies/glm/glm/glm.hpp"


GLfloat GRAVITY_AMOUNT = 0.001f;
GLfloat PI = 3.14159;
class GLFWobject
{
private:
    bool shouldApplyGravity;
    char shape;
    GLfloat size;
    GLfloat width;
    GLfloat height;
    GLfloat weight;
    GLint numSegments;
    std::vector<GLfloat> vertices;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 startingVelocity;
    GLfloat rotation;
    GLfloat travelAngle;
    GLfloat startingTravelAngle;
    GLfloat endingTravelAngle;
    glm::vec2 startingPosition;
    glm::vec2 endingPosition;
    std::vector<glm::vec2> collisions;
    int bottomBoundaryCount;
public:
    // Constructor declaration
    GLFWobject(char shape, GLfloat size, GLint numSegments, glm::vec2 position, glm::vec2 velocity, GLfloat rotation, bool shouldApplyGravity);

    void calculateVertices(const char shape, GLfloat size, std::vector<GLfloat> &vertices, GLint numSegments);

    // Getters
    bool getGravityEnable();
    char getShape();
    std::vector<GLfloat>& getVertices();
    // for circle radius and for width of rectangle
    GLfloat getSize() const;
    GLfloat getWeight() const;
    // for rectangle attributes
    GLfloat getWidth() const;
    GLfloat getHeight() const;
    GLfloat getTravelAngle();
    GLfloat getStartingTravelAngle();
    std::vector<glm::vec2> getCollisions();

    const glm::vec2& getPosition() const;
    const float getXPosition() const;
    const float getYPosition() const;
    const float getStartingXPosition() const;
    const float getStartingYPosition() const;
    const float getEndingXPosition() const;
    const float getEndingYPosition() const;
    const glm::vec2& getEndingPosition() const;
    const glm::vec2& getVelocity() const;
    const float getStartingXVelocity() const;
    const float getStartingYVelocity() const;
    const GLfloat getXVelocity();
    const GLfloat getYVelocity();
    const GLfloat getRotation() const;
    const int getBottomBoundaryCount() const;

    // Setters
    void setGravityEnable(bool flag);
    void setPosition(const glm::vec2& newPosition);
    void setXPosition(GLfloat newXPosition);
    void setYPosition(GLfloat newYPosition);
    void setVelocity(const glm::vec2& newVelocity);
    void setXVelocity(GLfloat newVelocity);
    void setYVelocity(GLfloat newVelocity);
    void setRotation(GLfloat newRotation);
    void setEndingPosition(const glm::vec2& position);

    void setWeight(GLfloat newWeight);
    void setTravelAngle(GLfloat newAngle);
    void setStartingPosition(glm::vec2 newPosition);
    void setStartingTravelAngle(GLfloat newAngle);
    void setStartingVelocity(glm::vec2 newVelocity);
    void setShape(char newShape);
    void setSize(GLfloat newSize);
    void setWidth(GLfloat newWidth);
    void setHeight(GLfloat newHeight);
    void updateBottomBoundaryCount();


    void addCollision();

    //Calculations
    void calculateAngleOfTravel(GLfloat &angle);
    glm::vec2 calculateVelocityFromAngle(GLfloat &angle);
    void updatePosition(GLfloat deltaTime);
    void applyGravity();

    void clear();

    // Destructor declaration
    ~GLFWobject();
};

// Constructor
GLFWobject::GLFWobject(const char shape, GLfloat size, GLint numSegments, glm::vec2 position, glm::vec2 velocity, GLfloat rotation, bool shouldApplyGravity)
    : shape(shape), size(size), numSegments(numSegments), position(position), velocity(velocity), rotation(rotation), shouldApplyGravity(shouldApplyGravity)
{
    calculateVertices(shape, size, vertices, numSegments);
    weight = getWeight();
    travelAngle = getTravelAngle();
    startingPosition = position;
    startingTravelAngle = getTravelAngle();
    startingVelocity = velocity;
}

// Destructor
GLFWobject::~GLFWobject()
{
}

void GLFWobject::calculateVertices(const char shape, GLfloat size, std::vector<GLfloat> &vertices, GLint numSegments)
{
    if (shape == 'c' || shape == 'C')
    {
        vertices.clear();
        vertices.reserve((numSegments + 1) * 2);
        vertices.push_back(0.0f); // Center point
        vertices.push_back(0.0f);
        for (int i = 0; i <= numSegments; ++i)
        {
            GLfloat theta = 2.0f * 3.14159f * static_cast<GLfloat>(i) / numSegments;
            vertices.push_back(size * std::cos(theta));
            vertices.push_back(size * std::sin(theta));
        }
    }
    else if (shape == 'r' || shape == 'R')
    {
        vertices.clear();
        vertices.reserve(8);

        // Calculate the four corner points of the rectangle
        float halfWidth = getWidth() / 2.0f;
        float halfHeight = getHeight() / 2.0f;

        vertices.push_back(-halfWidth);  // Bottom-left
        vertices.push_back(-halfHeight);


        vertices.push_back(halfWidth);   // Bottom-right
        vertices.push_back(-halfHeight);


        vertices.push_back(halfWidth);   // Top-right
        vertices.push_back(halfHeight);


        vertices.push_back(-halfWidth);  // Top-left
        vertices.push_back(halfHeight);
    }

    if (shape == 'p' || shape == 'P')
    {
        vertices.clear();
        vertices.reserve((numSegments + 1) * 2);
        vertices.push_back(0.0f); // Center point
        vertices.push_back(0.0f);
        for (int i = 0; i <= numSegments; ++i)
        {
            GLfloat theta = 2.0f * 3.14159f * static_cast<GLfloat>(i) / numSegments;
            vertices.push_back(size * std::cos(theta));
            vertices.push_back(size * std::sin(theta));
        }
    }
     
}

// Getters
bool GLFWobject::getGravityEnable()
{
    return shouldApplyGravity;
}

char GLFWobject::getShape()
{
    return shape;
}

std::vector<GLfloat>& GLFWobject::getVertices()
{
    return vertices;
}

GLfloat GLFWobject::getSize() const
{
    return size;
}

GLfloat GLFWobject::getWeight() const
{
    return size * GRAVITY_AMOUNT;
}

GLfloat GLFWobject::getWidth() const
{
    return size;
}

GLfloat GLFWobject::getHeight() const
{
    return size / 2.0f;
}

const glm::vec2& GLFWobject::getPosition() const
{
    return position;
}

const float GLFWobject::getXPosition() const
{
    return position[0];
}

const float GLFWobject::getYPosition() const
{
    return position[1];
}

const float GLFWobject::getStartingXPosition() const
{
    return startingPosition[0];
}

const float GLFWobject::getStartingYPosition() const
{
    return startingPosition[1];
}

const float GLFWobject::getEndingXPosition() const
{
    return endingPosition[0];
}

const float GLFWobject::getEndingYPosition() const
{
    return endingPosition[1];
}

const glm::vec2& GLFWobject::getEndingPosition() const
{
    return endingPosition;
}

const glm::vec2& GLFWobject::getVelocity() const
{
    return velocity;
}

const float GLFWobject::getStartingXVelocity() const
{
    return startingVelocity[0];
}

const float GLFWobject::getStartingYVelocity() const
{
    return startingVelocity[1];
}

const GLfloat GLFWobject::getXVelocity()
{
    return velocity[0];
}

const GLfloat GLFWobject::getYVelocity()
{
    return velocity[1];
}

const GLfloat GLFWobject::getRotation() const
{
    return rotation;
}

GLfloat GLFWobject::getTravelAngle()
{
    GLfloat angle = 0;
    calculateAngleOfTravel(angle);
    if (angle < 0.0)
    {
        angle = abs(angle);
        angle = 360 - angle;
    }
    return angle;
}

GLfloat GLFWobject::getStartingTravelAngle()
{
    return startingTravelAngle;
}

std::vector<glm::vec2> GLFWobject::getCollisions()
{
    return collisions;
}

const int GLFWobject::getBottomBoundaryCount() const
{
    return bottomBoundaryCount;
}

// Setters
void GLFWobject::setGravityEnable(bool flag)
{
    shouldApplyGravity = flag;
}
void GLFWobject::setPosition(const glm::vec2& newPosition)
{
    position = newPosition;
}

void GLFWobject::setXPosition(GLfloat newXPosition)
{
    position[0] = newXPosition;
}

void GLFWobject::setYPosition(GLfloat newYPosition)
{
    position[1] = newYPosition;
}

void GLFWobject::setVelocity(const glm::vec2& newVelocity)
{
    velocity = newVelocity;
}

void GLFWobject::setXVelocity(GLfloat newVelocity)
{
    velocity[0] = newVelocity;
}

void GLFWobject::setYVelocity(GLfloat newVelocity)
{
    velocity[1] = newVelocity;
}

void GLFWobject::setRotation(const GLfloat newRotation)
{
    rotation = newRotation;
}

void GLFWobject::setEndingPosition(const glm::vec2& position)
{
    endingPosition = position;
}


void GLFWobject::addCollision()
{
    collisions.push_back(position);
}

void GLFWobject::calculateAngleOfTravel(GLfloat &angle)
{
    float hypotenuse = hypot(getXVelocity(), getYVelocity());
    float sinAngle = getYVelocity() / hypotenuse;
    angle = asin(sinAngle);
    angle = angle * 180 / PI;
}

void GLFWobject::updatePosition(GLfloat deltaTime)
{
    // Rotate the velocity vector based on the rotation angle
    glm::mat2 rotationMatrix(cos(rotation), -sin(rotation), sin(rotation), cos(rotation));
    velocity = rotationMatrix * velocity;
    position += velocity * deltaTime;
}

void GLFWobject::applyGravity()
{
    if (GLFWobject::getYPosition() > -1.0f)
    {
        //std::cout << "GRAVITY!!!" << std::endl;
        velocity[1] -= weight;
    }
}


void GLFWobject::setWeight(GLfloat newWeight)
{
    weight = newWeight;
}

void GLFWobject::setTravelAngle(GLfloat newAngle)
{
    travelAngle = newAngle;
}

void GLFWobject::setStartingPosition(glm::vec2 newPosition)
{
    startingPosition = newPosition;
}

void GLFWobject::setStartingTravelAngle(GLfloat newAngle)
{
    startingTravelAngle = newAngle;
}

void GLFWobject::setStartingVelocity(glm::vec2 newVelocity)
{
    startingVelocity = newVelocity;
}

void GLFWobject::setShape(char newShape)
{
    shape = newShape;
}

void GLFWobject::setSize(GLfloat newSize)
{
    size = newSize;
}

void GLFWobject::setWidth(GLfloat newWidth)
{
    width = newWidth;
}

void GLFWobject::setHeight(GLfloat newHeight)
{
    height = newHeight;
}

void GLFWobject::clear()
{
    shouldApplyGravity = true;
    shape = '?';
    size = 0.0f;
    GLfloat width = 0.0f;
    GLfloat height = 0.0f;
    GLfloat weight = 0.0f;
    std::vector<GLfloat> vertices = {};
    glm::vec2 position = {};
    glm::vec2 velocity = {};
    glm::vec2 startingVelocity = {};
    GLfloat rotation = 0.0f;
    GLfloat travelAngle = 0.0f;
    GLfloat startingTravelAngle = 0.0f;
    GLfloat endingTravelAngle = 0.0f;
    glm::vec2 startingPosition = {};
    glm::vec2 endingPosition = {};
    std::vector<glm::vec2> collisions = {};
}

void GLFWobject::updateBottomBoundaryCount()
{
    bottomBoundaryCount++;
}

#endif // GLFWOBJECT_H