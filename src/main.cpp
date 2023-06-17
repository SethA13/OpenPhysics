// Include GLEW
#include <GL/glew.h>
#include "canvas/display/canvas.hpp"
#include <string>
#include <cstring>
#include <list>

#include <iostream>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include "..\dependancies\glm\glm\glm.hpp"

std::string checkTerminalParams(int argc, char** argv, std::string &initType, std::list<std::string> initEntries);

int main(int argc, char** argv)
{	
	struct windowContext
	{
		int windowHeight = 800;
		int windowWidth = 800;
	};
	std::list<std::string> initEntries{"GLFW"};
	std::string initType ="";

	// check if there is more than one argument and use the second one
	// (the first argument is the executable)
	initType = checkTerminalParams(argc, argv, initType, initEntries);

	std::cout << "init Type declared: " << initType << std::endl;

	struct windowContext displayPort;
	if (initType == "GLFW" || initType == "glfw")
	{
		std::cout << "Creating GLFW window..." << std::endl;
		// This is stupid to do, but I can't get getline() to play nice with char arrays so here we are.
		const int arrayLength = initType.length();
		char* windowName = new char[arrayLength+1];
		std::strcpy(windowName, initType.c_str());
		glfwWindowInit(displayPort.windowHeight, displayPort.windowWidth, windowName);
	}
	else
		std::cout << "No valid init declared.";
	
	return 0;
}

std::string checkTerminalParams(int argc, char** argv, std::string &initType, std::list<std::string> initEntries)
{
	if (argc > 1)
	{
		std::string arg1(argv[1]);
		initType = arg1;
	}
	else
	{
		std::cout << "Declare init (T)ype: ";
		std::cin >> initType;
	}

	if (initType == "T" || initType == "t")
	{
		std::cout	<< "Available init types; " << std::endl;
		for (std::string i : initEntries)
		{
			std::cout << i << std::endl;
		}
		checkTerminalParams(1, argv, initType, initEntries);
	}
	return initType;
}