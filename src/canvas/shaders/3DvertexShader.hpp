#include <GL/glew.h>

// Shader source code
const GLchar* vertexShaderSource = R"(#version 330 core

layout(location = 0) in vec3 aPosition; // 3D position attribute

uniform mat4 uModel; // Model transformation matrix
uniform mat4 uView;  // View transformation matrix
uniform mat4 uProjection; // Projection transformation matrix

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
)";