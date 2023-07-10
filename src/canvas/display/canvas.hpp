#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "../uiHandlers/keyCallback.hpp"
#include "../shaders/shaders.hpp"
#include "../../objects/definitions/objectsMasterInclude.hpp"
#include "../../forces/collisions.hpp"
#include "../../fileHandlers/inputProtocol.hpp"
#include "../../fileHandlers/outputProtocol.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <vector>
#include <unordered_map>
#include <chrono>

#include "../../../dependancies/glm/glm/glm.hpp"
#include "../../../dependancies/glm/glm/gtc/matrix_transform.hpp"
#include "../../../dependancies/glm/glm/gtc/type_ptr.hpp"
#include "../../../dependancies/glm/glm/gtx/string_cast.hpp"

float POINTSIZE = 0.005f;

// Function Prototypes
void glutDisplay();
int glutWindowInit(int argc, char** argv, int HEIGHT, int WIDTH, char *windowName, bool DEBUG);
void glutDrawCircle(const Point & center, int radius);


void glfwWindowInit(int HEIGHT, int WIDTH, char *windowName, std::string inFile, bool DEBUG);
void glfwCollisionLoop(GLFWwindow* &window, GLuint &shaderProgram, const std::vector<GLuint>& VAOs, std::vector<GLFWobject>& objects, int windowHeight, int windowWidth, std::string outFile, bool DEBUG);
std::vector<GLFWobject> createGLFWObjects(std::string &inFile, std::string &outFile, bool DEBUG);
std::vector<GLFWobject> scenarioPicker(std::string scenario, std::list<std::string> scenarioEntries, std::string &outFile);
std::vector<std::vector<GLfloat>> setupObjectVertices(std::vector<GLFWobject> &objects, bool DEBUG);
void setupVAOandVBO(int NUMVERTOBJS, GLuint VAO[], 
                    std::vector<GLuint> &VAOs, 
                    GLuint VBO[], 
                    std::vector<GLuint> &VBOs, 
                    std::vector<std::vector<GLfloat>> &allVertices,
                    bool DEBUG);
void GLFWCleanup(const std::vector<GLuint>& VAOs, const std::vector<GLuint>& VBOs, GLuint& shaderProgram);


void glutDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // blit blank display
    Point centerpoint(1040.0f/2, 720.0f/2);
    glutDrawCircle(centerpoint, 10);
    glutSwapBuffers();
    return;
}

int glutWindowInit(int argc, char** argv, int HEIGHT, int WIDTH, char *windowName, std::string inFile, bool DEBUG)
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


void glfwWindowInit(int HEIGHT, int WIDTH, char *windowName, std::string inFile, bool DEBUG)
{
    std::string outFile = "NULL";
    if (DEBUG == TRUE)
        {
            std::cout << "Init called!" << std::endl;
        }
        
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(-1);
    }

    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(HEIGHT, WIDTH, windowName, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Set the current context to the GLFW window
    glfwMakeContextCurrent(window);

    // Set the key callback function
    glfwSetKeyCallback(window, keyCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Error compiling vertex shader:\n" << infoLog << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Error compiling fragment shader:\n" << infoLog << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check shader program linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Error linking shader program:\n" << infoLog << std::endl;
        glfwTerminate();
        std::exit(-1);
    }

    // Delete the shaders as they're linked to the program now and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (DEBUG == TRUE)
    {
        std::cout << "Shaders deleted!" << std::endl;
    }
        
    std::vector<GLFWobject> objects = createGLFWObjects(inFile, outFile, DEBUG); // Update with all objects

    std::vector<std::vector<GLfloat>> allVertices = setupObjectVertices(objects, DEBUG); // for holding all vertices data
    
    int NUMVERTOBJS = objects.size();
    GLuint VAO[NUMVERTOBJS], VBO[NUMVERTOBJS];
    std::vector<GLuint> VAOs; // Update with VAOs
    std::vector<GLuint> VBOs; // update with VBOs
    glGenVertexArrays(NUMVERTOBJS, VAO);
    glGenBuffers(NUMVERTOBJS, VBO);

    setupVAOandVBO(NUMVERTOBJS, VAO, VAOs, VBO, VBOs, allVertices, DEBUG);

    glfwCollisionLoop(window, shaderProgram, VAOs, objects, HEIGHT, WIDTH, outFile, DEBUG);



    //cleanup on shutdown
    GLFWCleanup(VAOs, VBOs, shaderProgram);
    return;
}

std::vector<GLFWobject> createGLFWObjects(std::string &inFile, std::string &outFile, bool DEBUG)
{
    std::vector<GLFWobject> objects; // Update with all objects
    std::string scenario = "NULL";
    std::list<std::string> scenarioEntries{"circles", "rectangles", "points", "circle"};

    //If an infile is declared, attempt to read from it
    if(inFile != "NULL")
    {
        createObjectsFromInfile(objects, inFile);
    }
    else
    {
        std::cout << "Which scenario would you like to play? " << std::endl;
        std::cout << "Available scenarios; " << std::endl;
        for (std::string i : scenarioEntries)
        {
            std::cout << i << std::endl;
        }
        std::cin >> scenario;  
        objects = scenarioPicker(scenario, scenarioEntries, outFile);
    }
    if (DEBUG == TRUE)
    {
        std::cout << "Objects made, added to vector" << std::endl;
    }
    return objects;
}

std::vector<GLFWobject> scenarioPicker(std::string scenario, std::list<std::string> scenarioEntries, std::string &outFile)
{
    std::vector<GLFWobject> objects;
    bool flag = true;
    while (flag)
    {
        if (scenario == "circles")
        {
            flag = false;
            outFile = "circleDemo.ophy";
            GLFWobject circle1      ('c',               //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.85f, 0.5f},       //Starting Position -- {x,y}
                                    {0.003f, 0.003},    //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    TRUE);              //Gravity
            objects.push_back(circle1);

            GLFWobject circle2      ('c',               //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.3f, -0.1f},      //Starting Position -- {x,y}
                                    {0.002f, -0.003f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    TRUE);              //Gravity
            objects.push_back(circle2);
        }
        else if (scenario == "rectangles")
        {
            flag = false;
            outFile = "rectangleDemo.ophy";
            GLFWobject rectangle1   ('r',               //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {0.6f, 0.6f},       //Starting Position -- {x,y}
                                    {-0.01f, 0.0f},       //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    TRUE);             //Gravity
            objects.push_back(rectangle1);
            GLFWobject rectangle2   ('r',               //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {-0.3f, -0.2f},       //Starting Position -- {x,y}
                                    {0.003f, 0.005f},       //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    TRUE);             //Gravity
            objects.push_back(rectangle2);
        }
        else if (scenario == "points")
        {
            flag = false;
            outFile = "pointDemo.ophy";
            GLFWobject point1       ('p',               //Shape 
                                    POINTSIZE,            //Size
                                    1000,               //NumSegments
                                    {0.0f, 0.0f},       //Starting Position -- {x,y}
                                    {0.0001f, 0.002f},       //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    TRUE);             //Gravity
            objects.push_back(point1);
            GLFWobject point2       ('p',               //Shape 
                                    POINTSIZE,            //Size
                                    1000,               //NumSegments
                                    {-0.95f, 0.8f},       //Starting Position -- {x,y}
                                    {0.005f, -0.004f},       //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    TRUE);             //Gravity
            objects.push_back(point2);
        }
        else
        {
            std::cout << "No valid scenario given. Available scenarios; " << std::endl;
            for (std::string i : scenarioEntries)
            {
                std::cout << i << std::endl;
            }
            std::cin >> scenario;
        }
    }
    
    
    return objects;
}

std::vector<std::vector<GLfloat>> setupObjectVertices(std::vector<GLFWobject> &objects, bool DEBUG)
{
    std::vector<std::vector<GLfloat>> allVertices;
    for (auto& object : objects)
    {
        allVertices.push_back(object.getVertices());
    }
    
    if (DEBUG == TRUE)
    {
        std::cout << "Vertices added!" << std::endl;
    }
    return allVertices;
}

void setupVAOandVBO(int NUMVERTOBJS, GLuint VAO[], 
                    std::vector<GLuint> &VAOs, 
                    GLuint VBO[], 
                    std::vector<GLuint> &VBOs, 
                    std::vector<std::vector<GLfloat>> &allVertices, 
                    bool DEBUG)
{   
    // Bind and setup VAO and VBO for each object
    if (DEBUG == TRUE)
    {
        std::cout << "Attempting to bind VAO/VBO..." << std::endl;
    }
        
    for (int i = 0; i < NUMVERTOBJS; i++)
    {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        const std::vector<GLfloat>& vertices = allVertices[i];
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        VAOs.push_back(VAO[i]);
        VBOs.push_back(VBO[i]);
        if (DEBUG == TRUE)
        {
            std::cout << "VAO/VBO " << i << " done!" << std::endl;
        }
            
    }

    if (DEBUG == TRUE)
    {
        std::cout << "VAO/VBO bound, added to vector!" << std::endl;
        std::cout << "Calling main loop..." << std::endl;
    }
}

void glfwCollisionLoop(GLFWwindow* &window, GLuint &shaderProgram, const std::vector<GLuint>& VAOs, std::vector<GLFWobject>& objects, int windowHeight, int windowWidth, std::string outFile, bool DEBUG)
{
    if (DEBUG == TRUE)
    {
        std::cout << "Main loop called!" << std::endl;
    }
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        
        // Check and call events
        glfwPollEvents();

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Update positions of all circles
        for (auto& object : objects)
        {
            object.updatePosition(1);
        }

        // Perform collision detection and handling
        for (size_t i = 0; i < objects.size(); i++)
        {
            if (DEBUG == TRUE)
            {
                std::cout << "Current object to check window bounds; " << objects[i].getShape() << std::endl;
            }
            
            checkWindowBounds(objects[i], DEBUG);

            for (size_t j = i + 1; j < objects.size(); j++)
            {
                if (DEBUG == TRUE)
                {
                    std::cout << "Handling collisions for " << objects[i].getShape() << " and " << objects[j].getShape() << std::endl;
                }
                
                handleCollision(objects[i], objects[j], DEBUG);
            }
            if (objects[i].getGravityEnable())
            {
                objects[i].applyGravity();
            }

            if (objects[i].getYPosition() + objects[i].getSize() <= -1.0f)
            {
                if (objects[i].getYVelocity() <= 0.03f && objects[i].getYVelocity() >= -0.03f)
                {
                    objects[i].setYPosition((-1.0 + objects[i].getSize()));
                    objects[i].setGravityEnable(FALSE);
                    objects[i].setEndingPosition(objects[i].getPosition());
                }
                else
                    objects[i].setYPosition((-1.0 + objects[i].getSize()));
                
            }
            
        }

        // Draw the objects
        for (size_t i = 0; i < objects.size(); ++i)
        {
            // Update model matrix for the current object
            glm::mat4 modelMatrix = glm::mat4(1.0f);

            // Apply translation
            glm::vec2 circlePosition = objects[i].getPosition();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(objects[i].getPosition(), 0.0f));
            GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glBindVertexArray(VAOs[i]);
            glDrawArrays(GL_TRIANGLE_FAN, 0, objects[i].getVertices().size() / 2);
        }
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    glBindVertexArray(0);
    std::unordered_map<int, std::unordered_multimap<std::string, std::string>> objectMaps = createObjectMaps(objects);
    writeMapsToFile(objectMaps, outFile);
    
    return;
}


void GLFWCleanup(const std::vector<GLuint>& VAOs, const std::vector<GLuint>& VBOs, GLuint& shaderProgram)
{
    // Clean up resources
    for (size_t i = 0; i < VAOs.size(); i++)
    {
        glDeleteVertexArrays(1, &VAOs[i]);
        glDeleteBuffers(1, &VBOs[i]);
    }
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
}