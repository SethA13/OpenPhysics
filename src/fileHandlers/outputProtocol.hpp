#include <iostream>
#include <fstream>
#include <map>

#include "../objects/definitions/GLFWobject.hpp"

std::map<std::string, std::string> createObjectMap(GLFWobject &object);
void writeObjectToFile(std::map<std::string, std::string> &objectMap);

std::map<std::string, std::string> createObjectMap(GLFWobject &object)
{
    std::map<std::string, std::string> objectMap;
    objectMap["Shape"] = std::string(1, object.getShape());
    if (object.getShape() == 'c')
    {
        objectMap["Size"] = std::to_string(object.getSize());
    }
    else if (object.getShape() == 'r')
    {
        objectMap["Width"] = std::to_string(object.getWidth());
        objectMap["Height"] = std::to_string(object.getHeight());
    }
    objectMap["Weight"] = std::to_string(object.getWeight());
    objectMap["travelAngle"] = std::to_string(object.getTravelAngle());
    //TODO add in rotation of object once correct rotation calculation is done

    return objectMap;
}

void writeObjectToFile(std::map<std::string, std::string> &objectMap, std::string filename)
{
    std::ofstream outfile(filename);
    if (outfile.is_open())
    {
        for (auto& pair :objectMap)
        {
            outfile << pair.first << "; " << pair.second << std::endl;
        }
        outfile.close();
        std::cerr << "File "<< filename<< "Saved."<<std::endl;
    }
    else
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    
    return;
}