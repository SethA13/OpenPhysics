#ifndef GLFWOBJECT_H
#define GLFWOBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "../../../dependancies/glm/glm/glm.hpp"


GLfloat GRAVITY_AMOUNT = 0.0003f;
class GLFWobject
{
private:
    char shape;
    GLfloat size;
    GLfloat width;
    GLfloat height;
    GLint numSegments;
    std::vector<GLfloat> vertices;
    glm::vec2 position;
    glm::vec2 velocity;
    GLfloat rotation;
public:
    // Constructor declaration
    GLFWobject(char shape, GLfloat size, GLint numSegments, glm::vec2 position, glm::vec2 velocity, GLfloat rotation);

    void calculateVertices(const char shape, GLfloat size, std::vector<GLfloat> vertices, GLint numSegments);

    // Getters
    char getShape();
    const std::vector<GLfloat>& getVertices() const;
    // for circle radius and for width of rectangle
    GLfloat getSize() const;
    GLfloat getWidth() const;
    // for rectangle attributes
    GLfloat getHeight() const;

    const glm::vec2& getPosition() const;
    const glm::vec2& getVelocity() const;
    const GLfloat getXVelocity();
    const GLfloat getYVelocity();
    const GLfloat getRotation() const;

    // Setters
    void setPosition(const glm::vec2& newPosition);
    void setVelocity(const glm::vec2& newVelocity);
    void setXVelocity(GLfloat newVelocity);
    void setYVelocity(GLfloat newVelocity);
    void setRotation(GLfloat newRotation);


    void updatePosition(GLfloat deltaTime);
    void applyGravity();

    // Destructor declaration
    ~GLFWobject();
};

// Constructor
GLFWobject::GLFWobject(const char shape, GLfloat size, GLint numSegments, glm::vec2 position, glm::vec2 velocity, GLfloat rotation)
    : shape(shape), size(size), numSegments(numSegments), position(position), velocity(velocity), rotation(rotation)
{
    calculateVertices(shape, size, vertices, numSegments);
}

// Destructor
GLFWobject::~GLFWobject()
{
}

void GLFWobject::calculateVertices(const char shape, GLfloat size, std::vector<GLfloat> vertices, GLint numSegments)
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
        vertices.reserve(12);
        GLfloat width = size;
        GLfloat height = size / 2.0f;

        // Calculate the four corner points of the rectangle
        GLfloat halfWidth = width / 2.0f;
        GLfloat halfHeight = height / 2.0f;

        vertices.push_back(-halfWidth);  // Bottom-left
        vertices.push_back(-halfHeight);
        vertices.push_back(0.0f);

        vertices.push_back(halfWidth);   // Bottom-right
        vertices.push_back(-halfHeight);
        vertices.push_back(0.0f);

        vertices.push_back(halfWidth);   // Top-right
        vertices.push_back(halfHeight);
        vertices.push_back(0.0f);

        vertices.push_back(halfWidth);   // Top-right
        vertices.push_back(halfHeight);
        vertices.push_back(0.0f);

        vertices.push_back(-halfWidth);  // Top-left
        vertices.push_back(halfHeight);
        vertices.push_back(0.0f);

        vertices.push_back(-halfWidth);  // Bottom-left
        vertices.push_back(-halfHeight);
        vertices.push_back(0.0f);
    }
     
}

// Getters
char GLFWobject::getShape()
{
    return shape;
}

const std::vector<GLfloat>& GLFWobject::getVertices() const
{
    return vertices;
}

GLfloat GLFWobject::getSize() const
{
    return size;
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

const glm::vec2& GLFWobject::getVelocity() const
{
    return velocity;
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

// Setters
void GLFWobject::setPosition(const glm::vec2& newPosition)
{
    position = newPosition;
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

void GLFWobject::updatePosition(GLfloat deltaTime)
{
    position += velocity * deltaTime;
}

void GLFWobject::applyGravity()
{
    velocity[1] -= GRAVITY_AMOUNT;
}

#endif // GLFWOBJECT_H