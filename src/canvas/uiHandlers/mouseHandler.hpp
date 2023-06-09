#include <GL/freeglut.h>

void mouseHandler(int button, int state, int x, int y, bool left_click) 
{
    mouseMotionHandler(x, y);

    if (state == GLUT_DOWN) 
    {
        if (button == GLUT_LEFT_BUTTON) 
    {
    left_click = true;
    return;
    }
    }
}

int mouseMotionHandler(int x, int y) 
{
    return x, y;
}