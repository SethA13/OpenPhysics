#include "canvas/display/canvas.hpp"
#include <string>
#include <cstring>
#include <list>

#include <iostream>

void checkTerminalParams(int argc, char** argv, std::string &initType, std::list<std::string> initEntries, std::string &inFile, bool &DEBUG);

int main(int argc, char** argv)
{	
	bool DEBUG = FALSE;
	int windowHeight = 1000;
	int windowWidth = 1000;
	std::list<std::string> initEntries{"glfw", "glut"};
	std::string initType = "NULL";
	std::string inFile = "NULL";

	// check if there is more than one argument and use the second one
	// (the first argument is the executable)
	checkTerminalParams(argc, argv, initType, initEntries, inFile, DEBUG);

	if (initType == "glfw" || initType == "GLFW")
	{
		if (inFile != "NULL")
		{
			
		}
		
		std::cout << "Creating GLFW window..." << std::endl;
		// This is stupid to do, but I can't get getline() to play nice with char arrays so here we are.
		const int arrayLength = initType.length();
		char* windowName = new char[arrayLength+1];
		std::strcpy(windowName, initType.c_str());
		glfwWindowInit(windowHeight, windowWidth, windowName, inFile, DEBUG);
	}
	else if (initType == "glut" || initType == "GLUT")
	{
		std::cout << "Creating GLUT window..." << std::endl;
		// This is stupid to do, but I can't get getline() to play nice with char arrays so here we are.
		const int arrayLength = initType.length();
		char* windowName = new char[arrayLength+1];
		std::strcpy(windowName, initType.c_str());
		glutWindowInit(argc, argv, windowHeight, windowWidth, windowName, inFile, DEBUG);
		//not needed on return
		delete[] windowName;
	}
	else
		std::cout << "No valid init declared.";
	
	return 0;
}

void checkTerminalParams(int argc, char** argv, std::string &initType, std::list<std::string> initEntries, std::string &inFile, bool &DEBUG)
{
	if (argc > 3)
	{
		bool arg3 = argv[3];
		DEBUG = arg3;

		std::string arg2(argv[2]);
		inFile = arg2;

		std::string arg1(argv[1]);
		initType = arg1;
	}
	else if (argc > 2)
	{
		std::string arg2(argv[2]);
		inFile = arg2;

		std::string arg1(argv[1]);
		initType = arg1;
	}
	
	else if (argc > 1)
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
		std::cout << "After declaring init type, to add DEBUG messages, add a 1." << std::endl;
		std::cout << "Example; 'main.exe glfw  inFile.ophy 1' " << std::endl;
		checkTerminalParams(1, argv, initType, initEntries, inFile, DEBUG);
	}
	return;
}