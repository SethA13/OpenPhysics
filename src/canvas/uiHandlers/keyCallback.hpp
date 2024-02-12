#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../objects/definitions/objectsMasterInclude.hpp"
#include "../../../dependancies/glm/glm/glm.hpp"


struct objectCallbackData
{
    std::vector<GLFWobject>& objects;

    objectCallbackData(std::vector<GLFWobject>& objectsRef) : objects(objectsRef) {}
};

bool upKeyPressed = false;
bool downKeyPressed = false;
bool leftKeyPressed = false;
bool rightKeyPressed = false;

std::vector<GLFWobject> objects;
objectCallbackData objectsdata(objects);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void moveSnakeUp(std::vector<GLFWobject>& objects);
void moveSnakeDown(std::vector<GLFWobject>& objects);
void moveSnakeLeft(std::vector<GLFWobject>& objects);
void moveSnakeRight(std::vector<GLFWobject>& objects);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_UP)
    {
        if (action == GLFW_PRESS)
        {
            upKeyPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            upKeyPressed = false;
        }
    }
    if (key == GLFW_KEY_DOWN)
    {
        if (action == GLFW_PRESS)
        {
            downKeyPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            downKeyPressed = false;
        }
    }  
    if (key == GLFW_KEY_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftKeyPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            leftKeyPressed = false;
        }
    }
    if (key == GLFW_KEY_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightKeyPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            rightKeyPressed = false;
        }
    }
        
}

void moveSnakeUp(std::vector<GLFWobject>& objects)
{
    glm::vec2 lastPosition;
    for (int objectNumber = 0; objectNumber < objects.size(); objectNumber++)
    {   
        if (objectNumber == 0)
        {
            objects[objectNumber].setYPosition(objects[objectNumber].getYPosition() + 0.01);
        }
        
        else if (objectNumber != 0)
        {
            lastPosition = objects[objectNumber-1].getPosition();
            objects[objectNumber].setPosition(lastPosition);
        }
    }
    
}

void moveSnakeDown(std::vector<GLFWobject>& objects)
{
    glm::vec2 lastPosition;
    for (int objectNumber = 0; objectNumber < objects.size(); objectNumber++)
    {   
        if (objectNumber == 0)
        {
            objects[objectNumber].setYPosition(objects[objectNumber].getYPosition() - 0.01);
        }
        
        else if (objectNumber != 0)
        {
            lastPosition = objects[objectNumber-1].getPosition();
            objects[objectNumber].setPosition(lastPosition);
            if (objects[objectNumber - 1].getShape() == 'c' && objects[objectNumber].getShape() == 'c')
            {
                objects[objectNumber].setXPosition(objects[objectNumber - 1].getSize() + objects[objectNumber].getXPosition() + 0.1);
                objects[objectNumber].setYPosition(objects[objectNumber - 1].getSize() + objects[objectNumber].getYPosition() + 0.1);
            }
            else if (objects[objectNumber - 1].getShape() == 'c' && objects[objectNumber].getShape() == 'r')
            {
                /* code */
            }
            
        }
    }
}

void moveSnakeLeft(std::vector<GLFWobject>& objects)
{
    glm::vec2 lastPosition;
    for (int objectNumber = 0; objectNumber < objects.size(); objectNumber++)
    {   
        if (objectNumber == 0)
        {
            objects[objectNumber].setXPosition(objects[objectNumber].getXPosition() - 0.01);
        }
        
        else if (objectNumber != 0)
        {
            lastPosition = objects[objectNumber-1].getPosition();
            objects[objectNumber].setPosition(lastPosition);
        }
    }
}

void moveSnakeRight(std::vector<GLFWobject>& objects)
{
    glm::vec2 lastPosition;
    for (int objectNumber = 0; objectNumber < objects.size(); objectNumber++)
    {   
        if (objectNumber == 0)
        {
            objects[objectNumber].setXPosition(objects[objectNumber].getXPosition() + 0.01);
        }
        
        else if (objectNumber != 0)
        {
            lastPosition = objects[objectNumber-1].getPosition();
            objects[objectNumber].setPosition(lastPosition);
        }
    }
}
