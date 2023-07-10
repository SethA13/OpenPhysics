#ifndef OUTPUTPROTOCOL_H
#define OUTPUTPROTOCOL_H

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "../objects/definitions/GLFWobject.hpp"

std::unordered_map<int, std::unordered_multimap<std::string, std::string>> createObjectMaps(std::vector<GLFWobject>& objects);
void writeMapsToFile(std::unordered_map<int, std::unordered_multimap<std::string, std::string>>& objectMaps, std::string outFile);

std::unordered_map<int, std::unordered_multimap<std::string, std::string>> createObjectMaps(std::vector<GLFWobject>& objects)
{
    int count = 1;
    std::unordered_map<int, std::unordered_multimap<std::string, std::string>> objectMaps;
    for (size_t i = 0; i < objects.size(); i++)
    {
        std::unordered_multimap<std::string, std::string> objectMap;
        
        std::string endingString = std::to_string(objects[i].getEndingXPosition()) + ", " + std::to_string(objects[i].getEndingYPosition());
        objectMap.insert(std::pair<std::string, std::string>("Ending Position", endingString));
        //TODO add in rotation of object once correct rotation calculation is done
        for (auto& collision : objects[i].getCollisions())
        {
            std::string collisionString = std::to_string(collision[0]) + ", " + std::to_string(collision[1]);
            objectMap.insert(std::pair<std::string, std::string>("Collision", collisionString));
        }
        objectMap.insert(std::pair<std::string, std::string>("Ending Angle of Travel", std::to_string(objects[i].getTravelAngle())));
        objectMap.insert(std::pair<std::string, std::string>("Starting Angle of Travel", std::to_string(objects[i].getStartingTravelAngle())));
        objectMap.insert(std::pair<std::string, std::string>("Weight", std::to_string(objects[i].getWeight())));
        if (objects[i].getShape() == 'c')
        {
            objectMap.insert(std::pair<std::string, std::string>("Size", std::to_string(objects[i].getSize())));
            objectMap.insert(std::pair<std::string, std::string>("Shape", "Circle"));
        }
        else if (objects[i].getShape() == 'r')
        {
            objectMap.insert(std::pair<std::string, std::string>("Height", std::to_string(objects[i].getHeight())));
            objectMap.insert(std::pair<std::string, std::string>("Width", std::to_string(objects[i].getWidth())));
            objectMap.insert(std::pair<std::string, std::string>("Shape", "Rectangle"));
        }
        else
        {
            objectMap.insert(std::pair<std::string, std::string>("Shape", "Point"));
        }
        std::string startingString = std::to_string(objects[i].getStartingXPosition()) + ", " + std::to_string(objects[i].getStartingYPosition());
        objectMap.insert(std::pair<std::string, std::string>("Starting Position", startingString));
        objectMaps.insert(std::pair<int, std::unordered_multimap<std::string, std::string>>(count, objectMap));
        count++;
    }

    return objectMaps;
}



void writeMapsToFile(std::unordered_map<int, std::unordered_multimap<std::string, std::string>>& objectMaps, std::string outFile)
{
    std::ofstream outfile(outFile);
    if (outfile.is_open())
    {
        for (auto& map : objectMaps)
        {
            std::unordered_multimap<std::string, std::string>& objectMap = map.second;
            for (auto& pair : objectMap)
            {
                outfile << pair.first << "; " << pair.second << std::endl;
            }
            outfile << std::endl;
        }
        outfile.close();
        std::cerr << "File "<< outFile << " Saved."<<std::endl;
    }
    else
    {
        std::cerr << "Failed to open file: " << outFile << std::endl;
    }
    
    return;
}

#endif //OUTPUTPROTOCOL_H