#include <iostream>
#include <GL/glut.h>
#include <cmath>

// Circle class
class Circle
{
public:
    float radius;
    float posX;
    float posY;
    float velocityY;

    Circle(float r, float x, float y) : radius(r), posX(x), posY(y), velocityY(0.0f) {}

    // Update the circle's position based on gravity and handle window collisions
    void update(float gravity, float elasticity, float windowHeight)
    {
        velocityY += gravity;
        posY -= velocityY;

        // Reverse the direction and apply elasticity if the circle hits the window boundaries
        if (posY - radius < 0.0f)
        {
            posY = radius;
            velocityY = -velocityY * elasticity;
        } 
        else if (posY + radius > windowHeight)
        {
            posY = windowHeight - radius;
            velocityY = -velocityY * elasticity;
        }
    }

    // Draw the circle
    void draw()
    {
        glPushMatrix();
        glTranslatef(posX, posY, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; i++)
        {
            float theta = i * 3.14159f / 180.0f;
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }
};

// Window class
class Window
{
public:
    int width;
    int height;
    Circle* circle;
    float gravity;
    float elasticity;

    Window(int w, int h, float r) : width(w), height(h), circle(nullptr), gravity(0.1f), elasticity(0.8f) 
    {
        circle = new Circle(r, w / 2, h - r);
    }

    // Initialize OpenGL and create the window
    void initGL(int argc, char** argv) 
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(width, height);
        glutCreateWindow("Circle Gravity");

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
    }

    // GLUT display function
    static void display()
    {
        Window* window = getInstance();
        glClear(GL_COLOR_BUFFER_BIT);
    
        glMatrixMode(GL_MODELVIEW);  // Add this line
        glLoadIdentity();  // Add this line
    
        // Draw the circle
        window->circle->draw();

        glutSwapBuffers();
    }

    // GLUT idle function
    static void idle()
    {
        Window* window = getInstance();
        window->circle->update(window->gravity, window->elasticity, window->height);
        glutPostRedisplay();
    }

    // GLUT reshape function
    static void reshape(int width, int height)
    {
        Window* window = getInstance();
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        float orthoSize = window->circle->radius * 2.0f;

        if (width <= height)
            glOrtho(0.0, orthoSize, 0.0, orthoSize / aspectRatio, -1.0, 1.0);
        else
            glOrtho(0.0, orthoSize * aspectRatio, 0.0, orthoSize, -1.0, 1.0);

        window->width = width;
        window->height = height;
    }


    // GLUT keyboard function
    static void keyboard(unsigned char key, int x, int y)
    {
        if (key == 27)
        { // 27 is the ASCII value for the 'Esc' key
            Window* window = getInstance();
            delete window->circle;
            exit(0);
        }
    }

    // Get the instance of the Window class (Singleton pattern)
    static Window* getInstance()
    {
        static Window instance(0, 0, 0);
        return &instance;
    }

    // Start the main loop
    void run()
    {
        glutMainLoop();
    }
};

int main(int argc, char** argv) 
{
    int windowWidth = 0;
    int windowHeight = 0;
    float radius = 0.0;
    // Check command-line arguments
    if (argc < 4 && argc != 1)
    {
        std::cout << "Too few parameters given; 3 parameters must be provided, or none at all." << std::endl;
        std::cout << "Parameters must be given as; windowWidth windowHeight circleRadius" << std::endl;
        return -1;
    }
    if (argc >= 4) 
    {
        windowWidth = std::stoi(argv[1]);
        windowHeight = std::stoi(argv[2]);
        radius = std::stof(argv[3]);
    }
    else
    // Ask for parameters
    {
        std::cout << "Enter window width: ";
        std::cin >> windowWidth;
        std::cout << "Enter window height: ";
        std::cin >> windowHeight;
        std::cout << "Enter circle radius: ";
        std::cin >> radius;
    }

    // Parse command-line arguments


    Window window(windowWidth, windowHeight, radius);
    window.initGL(argc, argv);
    window.run();

    return 0;
}
