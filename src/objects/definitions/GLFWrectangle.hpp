#ifndef GLFWRECTANGLE_H
#define GLFWRECTANGLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class GLFWRectangle {
public:
    GLFWRectangle(float width, float height)
        : width(width), height(height)
    {
        calculateVertices();
    }

    void calculateVertices()
    {
        rectangleVertices.clear();
        rectangleVertices.reserve(12);

        // Calculate the four corner points of the rectangle
        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;

        rectangleVertices.push_back(-halfWidth);  // Bottom-left
        rectangleVertices.push_back(-halfHeight);
        rectangleVertices.push_back(0.0f);

        rectangleVertices.push_back(halfWidth);   // Bottom-right
        rectangleVertices.push_back(-halfHeight);
        rectangleVertices.push_back(0.0f);

        rectangleVertices.push_back(halfWidth);   // Top-right
        rectangleVertices.push_back(halfHeight);
        rectangleVertices.push_back(0.0f);

        rectangleVertices.push_back(halfWidth);   // Top-right
        rectangleVertices.push_back(halfHeight);
        rectangleVertices.push_back(0.0f);

        rectangleVertices.push_back(-halfWidth);  // Top-left
        rectangleVertices.push_back(halfHeight);
        rectangleVertices.push_back(0.0f);

        rectangleVertices.push_back(-halfWidth);  // Bottom-left
        rectangleVertices.push_back(-halfHeight);
        rectangleVertices.push_back(0.0f);
    }

    const std::vector<float>& getVertices() const
    {
        return rectangleVertices;
    }

    float getWidth() const
    {
        return width;
    }

    float getHeight() const
    {
        return height;
    }

private:
    float width;
    float height;
    std::vector<float> rectangleVertices;
};

#endif  //GLFWRECTANGLE_H