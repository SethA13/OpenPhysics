// Include GLEW
#include <GL/glew.h>
#include "canvas/display/canvas.hpp"
#include <string>

#include <iostream>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include "..\dependancies\glm\glm\glm.hpp"

int main(int argc, char** argv)
{
	std::string initType ="";
	// check if there is more than one argument and use the second one
	//  (the first argument is the executable)
	if (argc > 1)
	{
	std::string arg1(argv[1]);
	initType = arg1;
	}
	else
	{
		std::cout << "Declare 'GLUT' init or 'GLFW' init: ";
		std::cin >> initType;
	}

	std::cout << "init Type declared: " << initType << std::endl;
	
	if (initType == "GLFW" || initType == "glfw")
	{
		std::cout << "Creating GLFW window..." << std::endl;
		glfwWindowInit(800, 800);
	}
	else
		std::cout << "No valid init declared.";
	
	return 0;
}