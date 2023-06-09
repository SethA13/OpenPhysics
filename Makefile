##################################
 # codecompiler flags
##################################
PROJECTDIR = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

ifeq ($(OS),Windows_NT)
	CC = g++
	CFLAGS = -std=c++11 -Wall -Wextra -I$(PROJECTDIR)dependancies/glm/glm
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -L$(PROJECTDIR)dependancies/glm -Wl,-rpath=$(PROJECTDIR)dependancies/glm -lglm_shared

	SEP = \

else
	CC = g++
	CFLAGS = -std=c++11 -Wall -Wextra
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -lglm

	SEP = /
endif

TESTSRCSDIR = .\tests\src
TESTOBJSDIR = .\tests\bin\objs
TESTBINDIR = .\tests\bin
##################################
 # test declaration prototypes
##################################
GLUTTEST = glutTest
GLUTTEST_SRCS = $(TESTSRCSDIR)\glutTest.cpp
GLUTTEST_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(GLUTTEST_SRCS:.cpp=.o))

COLLISIONS = collisionTest
COLLISIONS_SRCS = $(TESTSRCSDIR)\collisionTest.cpp
COLLISIONS_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(COLLISIONS_SRCS:.cpp=.o))

PLANETS = planetTest
PLANETS_SRCS = $(TESTSRCSDIR)\planetTest.cpp
PLANETS_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(PLANETS_SRCS:.cpp=.o))

CIRCLE = circleTest
CIRCLE_SRCS = $(TESTSRCSDIR)\circleTest.cpp
CIRCLE_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(CIRCLE_SRCS:.cpp=.o))
#####################################
 # clean test declaration prototypes
#####################################
CLEAN_GLUTTEST = clean_glutTest
CLEAN_COLLISIONS = clean_collisions
CLEAN_PLANETS = clean_planets
CLEAN_CIRCLE = CLEAN_CIRCLE



PROJSRCSDIR = .\src
PROJOBJSDIR = .\bin\objs
PROJBINDIR = .\bin
#####################################
 # project declaration prototypes
#####################################
PROJECT = main
PROJECT_SRCS = $(PROJSRCSDIR)\main.cpp
PROJECT_OBJS = $(patsubst $(PROJSRCSDIR)\%.cpp, $(PROJOBJSDIR)\%.o, $(PROJECT_SRCS:.cpp=.o))
########################################
 # clean project declaration prototypes
########################################
CLEAN_PROJECT = clean_project


#########################################################################
 # 							Task Declarations
 #		all:
 #			compile everything
 #		clean_all:
 #			delete all compilation files
 #		project:
 #			compile project files
 #		clean_project:
 #			delete project compilation files
 #		tests:
 #			compile all the test files
 #		clean_tests:
 #			delete all compiled test files
 #		glutTest:
 #			compile glutTest
 # 		clean_glutTest:
 #			delete compilation files for glutTest
 # 		collisions:
 # 			compile collisions test
 # 		clean_collisions:
 # 			delete compilation files for collisions test
 #		planets:
 #			compile planets test
 #		clean_planets:
 #			delete compilation files for planets test
#########################################################################
all: tests project

clean_all: clean_tests clean_project

tests: glut collisions planets circle

clean_tests: $(CLEAN_GLUTTEST) $(CLEAN_COLLISIONS) $(CLEAN_PLANETS)


##############################################################
#						Test Files
##############################################################
#####################################
# for making the glut test file
#####################################
glut: $(GLUTTEST)
	@echo "glutTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(GLUTTEST).o' -Destination '$(TESTOBJSDIR)\$(GLUTTEST).o' -force" 

$(GLUTTEST): $(GLUTTEST_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

$(TESTOBJSDIR)\%.o: $(TESTSRCSDIR)\%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_GLUTTEST):
	del /Q $(TESTOBJSDIR)\$(GLUTTEST).o $(TESTBINDIR)\$(GLUTTEST).exe

#####################################
# for making the collisions test file
#####################################
collisions: $(COLLISIONS)
	@echo "collisionTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(COLLISIONS).o' -Destination '$(TESTOBJSDIR)\$(COLLISIONS).o' -force" 

$(COLLISIONS): $(COLLISIONS_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_COLLISIONS):
	del /Q $(TESTOBJSDIR)\$(COLLISIONS).o $(TESTBINDIR)\$(COLLISIONS).exe

#####################################
# for making the planets test file
#####################################
planets: $(PLANETS)
	@echo "planetTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(PLANETS).o' -Destination '$(TESTOBJSDIR)\$(PLANETS).o' -force"

$(PLANETS): $(PLANETS_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PLANETS):
	del /Q $(TESTOBJSDIR)\$(PLANETS).o $(TESTBINDIR)\$(PLANETS).exe

#####################################
# for making the circle test file
#####################################
circle: $(CIRCLE)
	@echo "circleTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(CIRCLE).o' -Destination '$(TESTOBJSDIR)\$(CIRCLE).o' -force"

$(CIRCLE): $(CIRCLE_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_CIRCLE):
	del /Q $(TESTOBJSDIR)\$(CIRCLE).o $(TESTBINDIR)\$(CIRCLE).exe

##############################################################
#						Project Files
##############################################################
project: $(PROJECT)
	@echo "project built!"
	powershell.exe -Command "Move-Item -Path '$(PROJSRCSDIR)\$(PROJECT).o' -Destination '$(PROJOBJSDIR)\$(PROJECT).o' -force"

$(PROJECT): $(PROJECT_OBJS)
	$(CC) $(CFLAGS) -o $(PROJBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PROJECT):
	del /Q $(PROJOBJSDIR)\$(PROJECT).o $(PROJBINDIR)\$(PROJECT).exe