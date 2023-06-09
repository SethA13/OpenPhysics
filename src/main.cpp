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
	std::string initType = "";
	std::cout << "Declare 'GLUT' init or 'GLFW' init: ";
	std::cin >> initType;

	std::cout << "init Type declared: " << initType << std::endl;

	/*********************************************
	 * Initialize glut w/o glfw or glut and glfw
	*********************************************/
	if (initType == "GLUT" || initType == "glut")
	{
		glutWindowInit(argc, argv);
	}
	else if (initType == "GLFW" || initType == "glfw")
	{
		glfwWindowInit(800, 800);
	}
	else
		std::cout << "No valid init declared.";
	
	return 0;
}