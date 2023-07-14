#include <iostream>
#include <liblas/liblas.hpp>
#include <GL/glut.h>

// Global variables
std::ifstream ifs;
liblas::ReaderFactory reader_factory;
liblas::Reader reader = reader_factory.CreateWithStream(ifs);
int width = 800;
int height = 600;

// OpenGL display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glBegin(GL_POINTS);

    while (reader.ReadNextPoint())
    {
        const liblas::Point& point = reader.GetPoint();

        // Extract X, Y, Z coordinates from the point
        double x = point.GetX();
        double y = point.GetY();
        double z = point.GetZ();

        // Render the point
        glVertex3d(x, y, z);
    }

    glEnd();

    glutSwapBuffers();
}

// OpenGL window reshape function
void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("LAZ Viewer");

    // Initialize OpenGL settings
    glEnable(GL_DEPTH_TEST);

    // Open the LAZ file
    try
    {
        reader = reader_factory.CreateWithStream(std::cin);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error opening LAZ file: " << e.what() << std::endl;
        return 1;
    }

    // Register GLUT callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Start the main GLUT loop
    glutMainLoop();

    // Clean up
    return 0;
}
