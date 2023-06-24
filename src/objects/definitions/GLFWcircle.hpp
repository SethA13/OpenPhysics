#ifndef GLFWCIRCLE_H
#define GLFWCIRCLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "../../../dependancies/glm/glm/glm.hpp"

class GLFWCircle {
public:
    GLFWCircle(float radius, GLint numSegments, glm::vec2 position, glm::vec2 velocity, glm::vec2 direction)
        : radius(radius), numSegments(numSegments), position(position), velocity(velocity), direction(direction)
    {
        calculateVertices();
    }

    void calculateVertices()
    {
        circleVertices.clear();
        circleVertices.reserve((numSegments + 1) * 2);
        circleVertices.push_back(0.0f); // Center point
        circleVertices.push_back(0.0f);
        for (int i = 0; i <= numSegments; ++i)
        {
            GLfloat theta = 2.0f * 3.14159f * static_cast<float>(i) / numSegments;
            circleVertices.push_back(radius * std::cos(theta));
            circleVertices.push_back(radius * std::sin(theta));
        }
    }

    const std::vector<GLfloat>& getVertices() const
    {
        return circleVertices;
    }

    GLfloat getRadius() const
    {
        return radius;
    }

    const glm::vec2& getPosition() const
    {
        return position;
    }

    const glm::vec2& getVelocity() const
    {
        return velocity;
    }

    const glm::vec2& getDirection() const
    {
        return direction;
    }

    void setPosition(const glm::vec2& newPosition)
    {
        position = newPosition;
    }

    void setVelocity(const glm::vec2& newVelocity)
    {
        velocity = newVelocity;
    }

    void setDirection(const glm::vec2& newDirection)
    {
        direction = newDirection;
    }

    void updatePosition(float deltaTime)
    {
        position += velocity * deltaTime;
    }

private:
    GLfloat radius;
    GLint numSegments;
    std::vector<GLfloat> circleVertices;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 direction;
};

#endif  // GLFWCIRCLE_H