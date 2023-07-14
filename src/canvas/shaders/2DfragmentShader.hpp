#include <GL/glew.h>

const GLchar* fragmentShaderSource = R"(
    #version 330 core
    out vec4 color;
    void main()
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
)";