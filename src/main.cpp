// Include GLEW
#include <GL/glew.h>
#include "canvas\display\canvas.hpp"

#include <iostream>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include "..\dependancies\glm\glm\glm.hpp"

int main(int argc, char** argv)
{
	int returnCode = 0;
	char initType[4];
	std::cout << "Declare 'GLUT' init or 'GLFW' init: ";
	std::cin >> initType;

	std::cout << "init Type declared: " << initType << std::endl;

	/*********************************************
	 * Initialize glut w/o glfw or glut and glfw
	*********************************************/
	if (initType == "GLUT" || initType == "glut")
	{
		returnCode = glutWindowInit(argc, argv);
		checkInit(returnCode, initType);
		std::cout << "finish init" << std::endl;
	}
	else if (initType == "GLFW" || initType == "glfw")
	{
		returnCode = glfwWindowInit(800, 800);
		checkInit(returnCode, initType);
		std::cout << "finish init" << std::endl;
	}
	else
		std::cout << "No valid init declared.";
	
	return 0;
}