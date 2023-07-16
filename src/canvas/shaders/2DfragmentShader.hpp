#include <GL/glew.h>

const GLchar* fragmentShaderSource = R"(
    #version 330 core
    uniform int numCollisions;
    out vec4 color;
    void main()
    {
        float red = float(numCollisions) / 10.0;
        color = vec4(red, 1.0 - red, 0.0, 1.0);
    }
)";