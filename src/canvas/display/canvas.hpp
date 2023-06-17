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

// Function Prototypes
void glutDisplay();
int glutWindowInit(int argc, char** argv);
void glfwWindowInit(int WIDTH, int HEIGHT);
void glfwMainLoop(GLFWwindow* &window, GLuint shaderProgram, GLuint VAO, GLFWCircle circle);
void checkInit(int returnCode, std::string initType);
void ModelInit(GLuint &shaderProgram, const Circle& circle);
void setupCircleRendering(GLuint& vao, GLuint& vbo, GLuint &shaderProgram);
void GLFWCleanup(GLuint &VAO, GLuint &VBO, GLuint &shaderProgram);


void glutDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();
    glFlush();
    return;
}

int glutWindowInit(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1040, 720);
    glutCreateWindow("This window name");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(0, 1040.0, 720.0, 0, 0, 1); // Orient and define grid
    glutDisplayFunc(glutDisplay);
    glutMainLoop();
    return 0;
}



void glfwWindowInit(int HEIGHT, int WIDTH, char *windowName)
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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Circle", nullptr, nullptr);
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
    GLFWCircle circle(0.2f,     //Radius
                  1000);    //Numsegments

    // Set up vertex data and attribute pointers for circle
    const std::vector<GLfloat>& circleVertices = circle.getVertices();
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(GLfloat), circleVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glfwMainLoop(window, shaderProgram, VAO, circle);

    //cleanup on shutdown
    GLFWCleanup(VAO, VBO, shaderProgram);
    return;
}

void glfwMainLoop(GLFWwindow* &window, GLuint shaderProgram, GLuint VAO, GLFWCircle circle)
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

        // Draw the circle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.getVertices().size() / 2);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }
    return;
}


void setupCircleRendering(GLuint &vao, GLuint &vbo, GLuint &shaderProgram)
{
    // Create and bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create Vertex Buffer Object (VBO)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Define circle vertex data
    const int numSegments = 1000;  // Number of line segments to approximate the circle
    const float angleIncrement = 2.0f * 3.14159f / static_cast<float>(numSegments);
    std::vector<GLfloat> vertexData;
    vertexData.reserve((numSegments + 2) * 2);  // (x, y) for each vertex

    // Center vertex
    vertexData.push_back(0.0f);
    vertexData.push_back(0.0f);

    // Circle vertices
    for (int i = 0; i <= numSegments; ++i)
    {
        float angle = angleIncrement * static_cast<float>(i);
        float x = cosf(angle);
        float y = sinf(angle);
        vertexData.push_back(x);
        vertexData.push_back(y);
    }

    // Set vertex data into VBO
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    GLuint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelInit(GLuint shaderProgram, const Circle& circle)
{
    // Apply translation to the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(circle.getCenterPoint().getXPosition(), circle.getCenterPoint().getYPosition(), 0.0f));

    // Apply scaling to the model matrix
    model = glm::scale(model, glm::vec3(circle.getRadius(), circle.getRadius(), 1.0f));

    // Pass the model matrix to the shader
    GLint modelUniformLocation = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    // Draw a filled circle using triangle fan
    const int numSegments = 1000;  // Number of line segments to approximate the circle
    const float angleIncrement = 2.0f * 3.14159f / static_cast<float>(numSegments);
    const float centerX = 0.0f;
    const float centerY = 0.0f;

    glBegin(GL_TRIANGLE_FAN);
    glVertexAttrib3f(0, 1.0f, 1.0f, 1.0f);  // Set circle color to white

    glVertexAttrib2f(1, centerX, centerY);  // Center point of the circle

    for (int i = 0; i <= numSegments; ++i)
    {
        float angle = angleIncrement * static_cast<float>(i);
        float x = centerX + circle.getRadius() * cosf(angle);
        float y = centerY + circle.getRadius() * sinf(angle);
        glVertexAttrib2f(2, x, y);  // Vertex position
        glDrawArrays(GL_POINTS, 0, 1);
    }
    glEnd();
}



void checkInit(int returnCode, std::string initType)
{
    if (returnCode < 0)
    {
        std::cout << initType << " failed to initialize properly." << std::endl;
		std::exit;
    }
    else
        std::cout << "Initialization success!" << std::endl;
}

void GLFWCleanup(GLuint &VAO, GLuint &VBO, GLuint &shaderProgram)
{
    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
}