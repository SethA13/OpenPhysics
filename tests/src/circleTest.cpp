#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

// Include GLM
#include "..\..\dependancies\glm\glm\glm.hpp"

// Prototypes
int animationOP();
int staticOP();
class Circle {
public:
    Circle(float radius, GLint numSegments, glm::vec2 m_position)
        : radius(radius), numSegments(numSegments), m_position(m_position)
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

    float getYPosition()
    {
        return m_position.y;
    }
    void setYPosition(float Ypos)
    {
        m_position.y = Ypos;
    }
private:
    GLfloat radius;
    GLint numSegments;
    std::vector<GLfloat> circleVertices;
    glm::vec2 m_position;
};

// Window dimensions
const GLuint WIDTH = 1040, HEIGHT = 720;

// Shader source code
const GLchar* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 position;
    uniform mat4 model;
    void main()
    {
        gl_Position = model * vec4(position, 0.0, 1.0);
    }
)";

const GLchar* fragmentShaderSource = R"(
    #version 330 core
    out vec4 color;
    void main()
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
)";

// Function to handle key presses
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char** argv)
{
    std::string initType ="";
    // check if there is more than one argument and use the second one
    //  (the first argument is the executable)
    if (argc > 1)
    {
        std::string arg1(argv[1]);
        initType = arg1;
    }
    else
    {
        std::cout << "Declare which option to use (animation or static): ";
		std::cin >> initType;
    }

    std::cout << "Declared option: " << initType << std::endl;

    if (initType == "animation")
    {
        animationOP();
    }
    else if (initType == "static")
    {
        staticOP();
    }
    

    return 0;
}

int animationOP()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Circle Animation", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
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
        return -1;
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
        return -1;
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
        return -1;
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
        return -1;
    }
    // Delete the shaders as they're linked into the program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers
    GLfloat vertices[] = 
    {
        // Positions         // Colors
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Create circle object
    Circle circle(0.1f, 1000, glm::vec2(0.0f, 1.0f));

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been triggered
        glfwPollEvents();

        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the circle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        circle.setYPosition(circle.getYPosition() - 0.005f); // Update circle position
        glUniform1f(glGetUniformLocation(shaderProgram, "posY"), circle.setYPosition());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0;
}
