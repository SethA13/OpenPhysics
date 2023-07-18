#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../dependancies/glm/glm/glm.hpp"
#include "../../dependancies/glm/glm/gtc/matrix_transform.hpp"
#include "../../dependancies/glm/glm/gtc/type_ptr.hpp"

// Vertex shader source code
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 position;
    layout (location = 1) in vec2 texCoords;
    out vec2 TexCoords;
    uniform mat4 model;
    uniform mat4 projection;
    void main()
    {
        gl_Position = projection * model * vec4(position, 0.0, 1.0);
        TexCoords = texCoords;
    })";

// Fragment shader source code
const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoords;
    out vec4 FragColor;
    uniform sampler2D textureSampler;
    void main()
    {
        FragColor = texture(textureSampler, TexCoords);
    })";

int main()
{
    // Initialize GLFW and create a window
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Billboard Example", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewInit();

    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Create quad geometry
    GLfloat vertices[] = {
        // Positions    // Texture coordinates
        -0.5f,  0.5f,   0.0f, 1.0f,
         0.5f,  0.5f,   1.0f, 1.0f,
         0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f,   0.0f, 0.0f
    };
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load billboard texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set texture parameters and load image data here

    // Set up rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the billboard
        glUseProgram(shaderProgram);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // Handle input and update the window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();
    return 0;
}
