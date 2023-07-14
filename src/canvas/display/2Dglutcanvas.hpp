#include <GL/glew.h>
#include <GL/glut.h>

#include <assert.h>
#include <cmath>

#include "../../objects/definitions/point.hpp"


// Function Prototypes
void glutDisplay();
int glutWindowInit(int argc, char** argv, int WIDTH, int HEIGHT, char *windowName, bool DEBUG);
void glutDrawCircle(const Point & center, int radius);

void glutDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // blit blank display
    Point centerpoint(1040.0f/2, 720.0f/2);
    glutDrawCircle(centerpoint, 10);
    glutSwapBuffers();
    return;
}

int glutWindowInit(int argc, char** argv, int WIDTH, int HEIGHT, char *windowName, std::string inFile, bool DEBUG)
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