// Include GLEW
#include <GL/glew.h>

#include "canvas\display\canvas.hpp"

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include "..\dependancies\glm\glm\glm.hpp"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1040, 720);
    glutCreateWindow("This window name");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}