#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../src/objects/definitions/gravityGLFWcircle.hpp"
#include "../../src/forces/forcesMasterInclude.hpp"

// GLFW error callback
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // Set GLFW error callback
    glfwSetErrorCallback(errorCallback);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Gravity Example", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Set up the circle
    GravityGLFWCircle circle(0.2f, 30);

    // Set up the gravity
    Gravity gravity(circle, 0.5f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Apply gravity to the circle
        gravity.applyGravity(0.01f);

        // Draw the circle
        const std::vector<GLfloat>& vertices = circle.getVertices();
        glLoadIdentity();
        glTranslatef(vertices[0], vertices[1], 0.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size() / 2));

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
