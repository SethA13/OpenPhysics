#include <GL/glut.h>
#include "canvas.hpp"

// Include GLEW
//#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

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