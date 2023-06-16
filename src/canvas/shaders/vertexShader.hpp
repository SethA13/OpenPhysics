#include <GL/glew.h>

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