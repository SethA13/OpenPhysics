#ifndef GRAVITYGLFWCIRCLE_H
#define GRAVITYGLFWCIRCLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "../../forces/gravity.hpp"

class GravityGLFWCircle : public GravityObject {
public:
    GravityGLFWCircle(float radius, GLint numSegments)
        : radius(radius), numSegments(numSegments), positionX(0.0f), positionY(0.0f)
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

    void applyGravity(float deltaTime) override
    {
        positionY -= deltaTime;
    }

    GLfloat getPositionX() const
    {
        return positionX;
    }

    GLfloat getPositionY() const
    {
        return positionY;
    }

private:
    GLfloat radius;
    GLint numSegments;
    std::vector<GLfloat> circleVertices;
    GLfloat positionX;
    GLfloat positionY;
};

#endif  // GRAVITYGLFWCIRCLE_H