#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "../uiHandlers/keyCallback.hpp"
#include "../uiHandlers/mouseHandler.hpp"
#include "../shaders/2Dshaders.hpp"
#include "../../objects/definitions/objectsMasterInclude.hpp"
#include "../../forces/collisions.hpp"
#include "../../fileHandlers/inputProtocol.hpp"
#include "../../fileHandlers/outputProtocol.hpp"
#include "../uiHandlers/scenarioPicker.hpp"

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

void glfwWindowInit(int WIDTH, int HEIGHT, char *windowName, std::string inFile, std::string &scenario, std::list<std::string> &scenarioEntries, bool DEBUG);
void glfwCollisionLoop(GLFWwindow* &window, GLuint &shaderProgram, const std::vector<GLuint>& VAOs, std::vector<GLFWobject>& objects, int windowWidth, int windowHeight, std::string outFile, bool DEBUG);
std::vector<GLFWobject> createGLFWObjects(std::string &inFile, std::string &outFile, std::string &scenario, std::list<std::string> &scenarioEntries, bool DEBUG);
std::vector<std::vector<GLfloat>> setupObjectVertices(std::vector<GLFWobject> &objects, bool DEBUG);
void setupVAOandVBO(int NUMVERTOBJS, GLuint VAO[], 
                    std::vector<GLuint> &VAOs, 
                    GLuint VBO[], 
                    std::vector<GLuint> &VBOs, 
                    std::vector<std::vector<GLfloat>> &allVertices,
                    bool DEBUG);
void GLFWCleanup(const std::vector<GLuint>& VAOs, const std::vector<GLuint>& VBOs, GLuint& shaderProgram);


void glfwWindowInit(int WIDTH, int HEIGHT, char *windowName, std::string inFile, std::string &scenario, std::list<std::string> &scenarioEntries, bool DEBUG)
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

    // Get the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    // Get the work area of the monitor
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    int monitorWidth = mode->width;
    int monitorHeight = mode->height;

    // Calculate the window position for centering
    int windowPosX = (monitorWidth - WIDTH) / 2;
    int windowPosY = ((monitorHeight - HEIGHT) / 2 - 10);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowName, nullptr, nullptr);
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

    // Set the window position
    glfwSetWindowPos(window, windowPosX, windowPosY);

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
        
    std::vector<GLFWobject> objects = createGLFWObjects(inFile, outFile, scenario, scenarioEntries, DEBUG); // Update with all objects

    std::vector<std::vector<GLfloat>> allVertices = setupObjectVertices(objects, DEBUG); // for holding all vertices data
    
    int NUMVERTOBJS = objects.size();
    GLuint VAO[NUMVERTOBJS], VBO[NUMVERTOBJS];
    std::vector<GLuint> VAOs; // Update with VAOs
    std::vector<GLuint> VBOs; // update with VBOs
    glGenVertexArrays(NUMVERTOBJS, VAO);
    glGenBuffers(NUMVERTOBJS, VBO);

    setupVAOandVBO(NUMVERTOBJS, VAO, VAOs, VBO, VBOs, allVertices, DEBUG);

    glfwCollisionLoop(window, shaderProgram, VAOs, objects, WIDTH, HEIGHT, outFile, DEBUG);



    //cleanup on shutdown
    GLFWCleanup(VAOs, VBOs, shaderProgram);
    return;
}

std::vector<GLFWobject> createGLFWObjects(std::string &inFile, std::string &outFile, std::string &scenario, std::list<std::string> &scenarioEntries, bool DEBUG)
{
    std::vector<GLFWobject> objects; // Update with all objects

    //If an infile is declared, attempt to read from it
    if(inFile != "NULL")
    {
        objects = createObjectsFromMap(inFile);
    }
    else if (scenario == "NULL")
    {
        std::cout << "Available scenarios; " << std::endl;
        for (std::string i : scenarioEntries)
        {
            std::cout << i << std::endl;
        }
        std::cout << "Which scenario would you like to play? ";
        std::cin >> scenario;  
        objects = scenarioPicker(scenario, scenarioEntries, outFile);
    }
    else if (scenario != "NULL")
    {
        objects = scenarioPicker(scenario, scenarioEntries, outFile);
    }
    
    if (DEBUG == TRUE)
    {
        std::cout << "Objects made, added to vector" << std::endl;
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

void glfwCollisionLoop(GLFWwindow* &window, GLuint &shaderProgram, const std::vector<GLuint>& VAOs, std::vector<GLFWobject>& objects, int windowWidth, int windowHeight, std::string outFile, bool DEBUG)
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
                if (objects[i].getYVelocity() <= 0.3f)
                {
                    objects[i].setYPosition((-1.0 + objects[i].getSize()));
                    objects[i].setGravityEnable(FALSE);
                    objects[i].setYVelocity(0.0);
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