#include "canvas/display/2Dcanvas.hpp"
#include "canvas/display/2Dglutcanvas.hpp"
#include <string>
#include <cstring>
#include <list>
#include <filesystem>

#include <iostream>

void checkTerminalParams(	int argc, char** argv, 
							std::string &initType, 
							std::list<std::string> initEntries, 
							std::string &inFile, 
							std::string &scenario, 
							std::list<std::string> &scenarioEntries, 
							bool &DEBUG);

int main(int argc, char** argv)
{	
	bool DEBUG = FALSE;
	int windowWidth = 1000;
	int windowHeight = 1000;
	
	std::list<std::string> initEntries{	"1. glfw",
	 									"2. glut",
										"3. LAS/LAZ"};
	std::string initType = "NULL";
	std::string inFile = "NULL";
	std::string scenario = "NULL";
	std::list<std::string> scenarioEntries{ "1. circles", 
                                            "2. rectangles", 
                                            "3. points", 
                                            "4. circle to rectangle", 
                                            "5. circle to point", 
                                            "6. rectangle to point", 
                                            "7. all shapes",
                                            "8. SRS scenario 1",
                                            "9. SRS scenario 2",
                                            "10. SRS scenario 3"};

	// check if there is more than one argument and use the second one
	// (the first argument is the executable)
	checkTerminalParams(argc, argv, initType, initEntries, inFile, scenario, scenarioEntries, DEBUG);

	if (initType == "glfw" || initType == "GLFW")
	{	
		std::cout << "Creating GLFW window..." << std::endl;
		// This is stupid to do, but I can't get getline() to play nice with char arrays so here we are.
		const int arrayLength = initType.length();
		char* windowName = new char[arrayLength + 1];
		std::strcpy(windowName, initType.c_str());
		glfwWindowInit(windowWidth, windowHeight, windowName, inFile, scenario, scenarioEntries, DEBUG);
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

void checkTerminalParams(	int argc, char** argv, 
							std::string &initType, 
							std::list<std::string> initEntries, 
							std::string &inFile, 
							std::string &scenario, 
							std::list<std::string> &scenarioEntries, 
							bool &DEBUG)
{
	if (argc > 4)
	{
		bool arg4 = argv[4];
		DEBUG = arg4;

		std::string arg3(argv[3]);
		scenario = arg3;

		std::string arg2(argv[2]);
		inFile = arg2;

		std::string arg1(argv[1]);
		initType = arg1;
	}
	else if (argc > 3)
	{
		std::string arg3(argv[3]);
		scenario = arg3;

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

		std::cout << "Declare (S)cenario. If scenario is unknown, type 'NULL'; ";
		std::cin >> scenario;
	}
	else
	{
		std::cout << "Declare init (T)ype: ";
		std::cin >> initType;

		std::cout << "Declare (S)cenario. If scenario is unknown, type 'NULL'; ";
		std::cin >> scenario;
	}

	if (initType == "T" || initType == "t")
	{
		std::cout	<< "Available init types; " << std::endl;
		for (std::string i : initEntries)
		{
			std::cout << i << std::endl;
		}
		std::cout << "After declaring init type, you may also declare an input file and a scenario" << std::endl;
		std::cout << "Usage; 'main.exe glfw  inFile.ophy scenario_number debug_enable' " << std::endl;
		checkTerminalParams(1, argv, initType, initEntries, inFile, scenario, scenarioEntries, DEBUG);
	}

	if (scenario == "S" || scenario == "s")
	{
		for (std::string i : scenarioEntries)
		{
			std::cout << i << std::endl;
		}
	}
	
	if (!std::filesystem::exists(inFile) && inFile != "NULL")
	{
		std::cout << "Declared file doesn't exist. Exiting..." << std::endl;
		std::exit(-1);
	}
	
	return;
}