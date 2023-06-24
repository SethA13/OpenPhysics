#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "../uiHandlers/keyCallback.hpp"
#include "../shaders/shaders.hpp"
#include "../../objects/definitions/objectsMasterInclude.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "../../../dependancies/glm/glm/glm.hpp"
#include "../../../dependancies/glm/glm/gtc/matrix_transform.hpp"
#include "../../../dependancies/glm/glm/gtc/type_ptr.hpp"
#include "../../../dependancies/glm/glm/gtx/string_cast.hpp"

// Function Prototypes
void glutDisplay();
int glutWindowInit(int argc, char** argv, char *windowName);
void glutDrawCircle(const Point & center, int radius);


void glfwCircleWindowInit(int HEIGHT, int WIDTH, char *windowName);
void glfwCircleCollisionLoop(GLFWwindow* window, GLuint shaderProgram, const std::vector<GLuint>& VAOs, std::vector<GLFWCircle>& circles, int windowHeight, int windowWidth);
void GLFWCleanup(const std::vector<GLuint>& VAOs, const std::vector<GLuint>& VBOs, GLuint& shaderProgram);


void glutDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // blit blank display
    Point centerpoint(1040.0f/2, 720.0f/2);
    glutDrawCircle(centerpoint, 10);
    glutSwapBuffers();
    return;
}

int glutWindowInit(int argc, char** argv, char *windowName)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1040, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowName);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(0, 1040.0, 720.0, 0, -1, 1); // Orient and define grid
    glutDisplayFunc(glutDisplay);
    glutMainLoop();
    return 0;
}

void glutDrawCircle(const Point & center, int radius)
{
   assert(radius >= 1.0);
   const double increment = 1.0 / (double)radius;

   // begin drawing
   glBegin(GL_POLYGON);

   // go around the circle
   for (double radians = 0; radians < 3.14159 * 2.0; radians += increment)
      glVertex2f(center.getXPosition() + (radius * cos(radians)),
                 center.getYPosition() + (radius * sin(radians)));
   
   // complete drawing
   glEnd();   
}


void glfwCircleWindowInit(int HEIGHT, int WIDTH, char *windowName)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(-1);
    }

    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(HEIGHT, WIDTH, windowName, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Set the current context to the GLFW window
    glfwMakeContextCurrent(window);

    // Set the key callback function
    glfwSetKeyCallback(window, keyCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Error compiling vertex shader:\n" << infoLog << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Error compiling fragment shader:\n" << infoLog << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check shader program linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Error linking shader program:\n" << infoLog << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Delete the shaders as they're linked to the program now and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create the circle object
    GLFWCircle circle1   (0.2f,             //Radius
                         1000,              //Numsegments
                         {0.0f, -0.5f},    //Position
                         {0.0f, 0.002f},    //Velocity
                         {0.0f, 0.0f});     //Direction

    GLFWCircle circle2   (0.1f,             //Radius
                         1000,              //Numsegments
                         {0.0f, 0.5f},  //Position
                         {0.0f, -0.002f},   //Velocity
                         {0.0f, 0.0f});     //Direction     

    // Set up vertex data and attribute pointers for circle
    const std::vector<GLfloat>& circleVertices1 = circle1.getVertices();
    const std::vector<GLfloat>& circleVertices2 = circle2.getVertices();
    int NUMVERTOBJS = 2;
    GLuint VAO[NUMVERTOBJS], VBO[NUMVERTOBJS];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    
    // Bind and setup VAO and VBO for circle1 and circle2
    for (int i = 0; i < NUMVERTOBJS; i++)
    {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        const std::vector<GLfloat>& circleVertices = (i == 0) ? circleVertices1 : circleVertices2;
        // What the above line actually means;
        /******************************************
        const std::vector<GLfloat>& circleVertices;
        if (i == 0) 
        {
            circleVertices = circleVertices1;
        } 
        else 
        {
            circleVertices = circleVertices2;
        }
        ******************************************/
        // But can't do it this way because it wants an itnitializer
        glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(GLfloat), circleVertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    std::vector<GLuint> VAOs = { VAO[0], VAO[1] }; // Update with your VAOs
    std::vector<GLuint> VBOs = {VBO[0], VBO[1]};
    std::vector<GLFWCircle> circles = { circle1, circle2 }; // Update with your circles

    glfwCircleCollisionLoop(window, shaderProgram, VAOs, circles, HEIGHT, WIDTH);

    //cleanup on shutdown
    GLFWCleanup(VAOs, VBOs, shaderProgram);
    return;
}

void glfwCircleCollisionLoop(GLFWwindow* window, GLuint shaderProgram, const std::vector<GLuint>& VAOs, std::vector<GLFWCircle>& circles, int windowHeight, int windowWidth)
{
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Check and call events
        glfwPollEvents();

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Update positions of all circles
        for (auto& circle : circles)
        {
            circle.updatePosition(1);
        }

        // Perform collision detection and handling
        for (size_t i = 0; i < circles.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < circles.size(); ++j)
            {
                auto& circle1 = circles[i];
                auto& circle2 = circles[j];

                // Calculate distance between the centers of the circles
                glm::vec2 center1 = circle1.getPosition();
                glm::vec2 center2 = circle2.getPosition();
                float distance = glm::distance(center1, center2);

                // Check for collision
                if (distance <= circle1.getRadius() + circle2.getRadius())
                {
                    // Circles have collided

                    // Reverse the direction of both circles
                    glm::vec2 newDirection1 = -circle1.getDirection();
                    glm::vec2 newDirection2 = -circle2.getDirection();
                    circle1.setDirection(newDirection1);
                    circle2.setDirection(newDirection2);

                    glm::vec2 newVelocity1 = -circle1.getVelocity();
                    glm::vec2 newVelocity2 = -circle2.getVelocity();
                    circle1.setVelocity(newVelocity1);
                    circle2.setVelocity(newVelocity2);
                    std::cout << "Circle 1 position;" << glm::to_string(circle1.getPosition()) << std::endl;
                }
            }
        }

        // Draw the circles
        for (size_t i = 0; i < circles.size(); ++i)
        {
            auto& circle = circles[i];

            // Update model matrix for the current circle
            glm::mat4 modelMatrix = glm::mat4(1.0f);

            // Apply translation
            glm::vec2 circlePosition = circle.getPosition();

            // Perform collision detection with window bounds
            float radius = circle.getRadius();
            // if (circlePosition.x - radius < 0.0f || circlePosition.x + radius > windowWidth) 
            // {
            //     circle.setVelocity(-(circle.getVelocity()));  // Keep the circle within the left edge
            // }
            // if (circlePosition.y - radius < 0.0f || circlePosition.y + radius > windowHeight) 
            // {
            //     circle.setVelocity(-(circle.getVelocity()));  // Keep the circle within the bottom edge
            // }
            modelMatrix = glm::translate(modelMatrix, glm::vec3(circle.getPosition(), 0.0f));
            GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glBindVertexArray(VAOs[i]);
            glDrawArrays(GL_TRIANGLE_FAN, 0, circle.getVertices().size() / 2);
        }

        glBindVertexArray(0);
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    return;
}


void GLFWCleanup(const std::vector<GLuint>& VAOs, const std::vector<GLuint>& VBOs, GLuint& shaderProgram)
{
    // Clean up resources
    for (size_t i = 0; i < VAOs.size(); i++)
    {
        glDeleteVertexArrays(1, &VAOs[i]);
        glDeleteBuffers(1, &VBOs[i]);
    }
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
}


/**********************************************************
 * UNUSED FUNCTION VERSIONS
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * void glfwCircleMainLoop(GLFWwindow* &window, GLuint shaderProgram, GLuint VAO, GLFWCircle circle1, GLFWCircle circle2)
{
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Check and call events
        glfwPollEvents();

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Set model matrix
        GLfloat model[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f };

        // Pass the model matrix to the shader
        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

        // Update positions of both circles
        circle1.updatePosition(1);
        circle2.updatePosition(1);

        // Calculate distance between the centers of the circles
        glm::vec2 center1 = circle1.getPosition();
        glm::vec2 center2 = circle2.getPosition();
        float distance = glm::distance(center1, center2);

        // Check for collision
        if (distance < circle1.getRadius() + circle2.getRadius()) 
        {
            // Circles have collided

            // Reverse the direction of both circles
            glm::vec2 newDirection1 = -circle1.getDirection();
            glm::vec2 newDirection2 = -circle2.getDirection();
            circle1.setDirection(newDirection1);
            circle2.setDirection(newDirection2);
        }

        // Draw the circle
        for (int i = 0; i < sizeof(VAO); i++)
        {
            glBindVertexArray(VAO[1]);
            glDrawArrays(GL_TRIANGLE_FAN, 0, circle1.getVertices().size() / 2);
            glBindVertexArray(0);
        }
        

        // Swap the buffers
        glfwSwapBuffers(window);
    }
    return;
}
**********************************************************/