#ifndef INPUTPROTOCOL_H
#define INPUTPROTOCOL_H

#include <iostream>
#include <fstream>
#include <unordered_map>


#include "../objects/definitions/GLFWobject.hpp"

std::unordered_map<int, std::unordered_multimap<std::string, std::string>> createObjectMaps(std::vector<GLFWobject>& objects);
void createObjectsFromMap(std::vector<GLFWobject> &objects, std::string &inFile);


void createObjectsFromMap(std::vector<GLFWobject> &objects, std::string &inFile)
{
    std::unordered_map<int, std::unordered_multimap<std::string, std::string>> ObjectMap;
    std::unordered_multimap<std::string, std::string> attributeMap;
    std::ifstream file(inFile);

    // going line by line
    std::string line;

    /*
    * We only want 4 things;
    * Shape
    * Sizes (radius - circle, width, height - rectangle)
    * Starting position
    * Starting velocity
    */

    return;
}

#endif //INPUTPROTOCOL_H