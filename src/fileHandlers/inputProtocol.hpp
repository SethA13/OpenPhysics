#ifndef INPUTPROTOCOL_H
#define INPUTPROTOCOL_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>


#include "../objects/definitions/GLFWobject.hpp"

std::vector<GLFWobject> createObjectsFromMap(std::string &inFile);

void setAttributesFromMap(std::unordered_multimap<std::string, std::string>& objectMap, GLFWobject &object);


std::vector<GLFWobject> createObjectsFromMap(std::string &inFile)
{
    std::vector<GLFWobject> objects;
    std::ifstream file(inFile);

   if (file.is_open())
    {
        /*
        * We only want 4 things;
        * Shape
        * Sizes (radius - circle, width, height - rectangle)
        * Starting position
        * Starting velocity
        */
        std::string shape;
        GLfloat size;
        GLfloat width;
        GLfloat height;
        glm::vec2 startingPosition;
        glm::vec2 startingVelocity;
        
        GLFWobject object   ('?',           //Shape 
                            0.0f,           //Size
                            1000,           //NumSegments
                            {0.0f, 0.0f},   //Starting Position -- {x,y}
                            {0.0f, 0.0f},   //Starting Velocity -- {x,y}
                            0,              //Rotation -- in degrees
                            true);         //Gravity
        std::unordered_multimap<std::string, std::string> objectMap;

        std::string line;
        int objectCounter = 1;
        while (std::getline(file, line))
        {
            if (line.empty()) // Empty line indicates the end of an object's attributes
            {
                // call functions that constructor would call
                setAttributesFromMap(objectMap, object);
                object.calculateVertices(object.getShape(), object.getSize(), object.getVertices(), 1000);
                object.setWeight(object.getWeight());
                object.setTravelAngle(object.getTravelAngle());
                object.setStartingPosition(object.getPosition());
                object.setStartingTravelAngle(object.getTravelAngle());
                object.setStartingVelocity(object.getVelocity());

                std::cout << "Adding object " << objectCounter << " To object list." << std::endl;
                std::cout << "Shape; " << object.getShape() << std::endl;
                if (object.getShape() == 'c')
                {
                    std::cout << "Radius; " << object.getSize() << std::endl;
                }
                else if (object.getShape() == 'r')
                {
                    std::cout << "Width; " << object.getWidth() << std::endl;
                    std::cout << "Height; " << object.getHeight() << std::endl;
                }
                std::cout << "Position; " << object.getXPosition() << ", " << object.getYPosition() << std::endl;
                std::cout << "Velocity; " << object.getXVelocity() << ", " << object.getYVelocity() << std::endl;
                // Add the constructed object to the vector
                objects.push_back(object);
                objectCounter++;

                // Reset the object and objectMap for the next object
                object.clear();
                objectMap.clear();
            }
            else
            {
                // Split the line into attribute and value
                std::size_t delimiterPos = line.find(';');
                std::string attribute = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 2); // Skip the delimiter and space

                // Add the attribute-value pair to the objectMap
                objectMap.insert(std::make_pair(attribute, value));
            }
        }
        // Check if there are remaining attributes after the last empty line
        if (!objectMap.empty())
        {
            // Set the attributes for the last object and add it to the vector
            setAttributesFromMap(objectMap, object);
            objects.push_back(object);
        }
        
    }
    return objects;
}

void setAttributesFromMap(std::unordered_multimap<std::string, std::string>& objectMap, GLFWobject &object)
{
    for (auto& pair : objectMap)
    {
        const std::string& attribute = pair.first;
        const std::string& value = pair.second;

        if (attribute == "Starting Position")
        {
            std::size_t delimiterPos = value.find(',');
            if (delimiterPos != std::string::npos)
            {
                std::string xValueStr = value.substr(0, delimiterPos);
                std::string yValueStr = value.substr(delimiterPos + 2); // Skip the delimiter and space

                // Convert the string values to floats
                float xValue = std::stof(xValueStr);
                float yValue = std::stof(yValueStr);

                object.setPosition({xValue, yValue});
            }
        }
        else if (attribute == "Shape")
        {
            if (value == "Circle")
            {
                object.setShape('c');
            }
            else if (value == "Rectangle")
            {
                object.setShape('r');
            }
            else if (value == "Point")
            {
                object.setShape('p');
            } 
        }
        else if (attribute == "Size")
        {
            GLfloat size = std::stof(value);
            object.setSize(size);
        }
        else if (attribute == "Width")
        {
            GLfloat size = std::stof(value);
            object.setSize(size);
            object.setWidth(object.getWidth());
        }
        else if (attribute == "Height")
        {
            object.setHeight(object.getHeight());
        }
        else if (attribute == "Starting Velocity")
        {
            std::size_t delimiterPos = value.find(',');
            if (delimiterPos != std::string::npos)
            {
                std::string xValueStr = value.substr(0, delimiterPos);
                std::string yValueStr = value.substr(delimiterPos + 2); // Skip the delimiter and space

                // Convert the string values to floats
                float xValue = std::stof(xValueStr);
                float yValue = std::stof(yValueStr);

            object.setVelocity({xValue, yValue});
            }
        }
    }
}

#endif //INPUTPROTOCOL_H