##################################
 # codecompiler flags
##################################
PROJECTDIR = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

ifeq ($(OS),Windows_NT)
	CC = g++
	CFLAGS = -std=c++11 -Wall -Wextra -I$(PROJECTDIR)dependancies/glm/glm
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -L$(PROJECTDIR)dependancies/glm -Wl,-rpath=$(PROJECTDIR)dependancies/glm -lglm_shared
else
	CC = g++
	CFLAGS = -std=c++11 -Wall -Wextra
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -lglm
endif

TESTSRCSDIR = .\tests\src
TESTOBJSDIR = .\tests\bin\objs
TESTBINDIR = .\tests\bin
##################################
 # test declaration prototypes
##################################
GLUTTEST = glutTest
GLUTTEST_SRCS = $(TESTSRCSDIR)\$(GLUTTEST).cpp
GLUTTEST_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(GLUTTEST_SRCS:.cpp=.o))

COLLISIONS = collisionTest
COLLISIONS_SRCS = $(TESTSRCSDIR)\$(COLLISIONS).cpp
COLLISIONS_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(COLLISIONS_SRCS:.cpp=.o))

PLANETS = planetTest
PLANETS_SRCS = $(TESTSRCSDIR)\$(PLANETS).cpp
PLANETS_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(PLANETS_SRCS:.cpp=.o))

CIRCLE = circleTest
CIRCLE_SRCS = $(TESTSRCSDIR)\$(CIRCLE).cpp
CIRCLE_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(CIRCLE_SRCS:.cpp=.o))

RECTANGLE = rectangleTest
RECT_SRCS = $(TESTSRCSDIR)\$(RECTANGLE).cpp
RECT_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(RECT_SRCS:.cpp=.o))

POINT = pointTest
POINT_SRCS = $(TESTSRCSDIR)\$(POINT).cpp
POINT_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(POINT_SRCS:.cpp=.o))
#####################################
 # clean test declaration prototypes
#####################################
CLEAN_GLUTTEST = clean_glutTest
CLEAN_COLLISIONS = clean_collisions
CLEAN_PLANETS = clean_planets
CLEAN_CIRCLE = clean_circle
CLEAN_RECTANGLE = clean_rectangle
CLEAN_POINT = clean_point


PROJSRCSDIR = .\src
PROJOBJSDIR = .\bin\objs
PROJBINDIR = .\bin

OBJSRCDIR = $(PROJSRCSDIR)\objects\functions

CIRCLEOBJ = circle
POINTOBJ = point
RECTOBJ = rectangle
OBJOBJ = object
VELOCITYOBJ = velocity
#####################################
 # project declaration prototypes
#####################################
PROJECT = main
PROJECT_SRCS = $(PROJSRCSDIR)\main.cpp $(OBJSRCDIR)\$(CIRCLEOBJ).cpp $(OBJSRCDIR)\$(POINTOBJ).cpp $(OBJSRCDIR)\$(RECTOBJ).cpp $(OBJSRCDIR)\$(OBJOBJ).cpp $(OBJSRCDIR)\$(VELOCITYOBJ).cpp 
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

tests: glut collisions planets circle rectangle point

clean_tests: $(CLEAN_GLUTTEST) $(CLEAN_COLLISIONS) $(CLEAN_PLANETS) $(CLEAN_CIRCLE) $(CLEAN_RECTANGLE) $(CLEAN_POINT)


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

#####################################
# for making the rectangle test file
#####################################
rectangle: $(RECTANGLE)
	@echo "rectangleTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(RECTANGLE).o' -Destination '$(TESTOBJSDIR)\$(RECTANGLE).o' -force"

$(RECTANGLE): $(RECT_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_RECTANGLE):
	del /Q $(TESTOBJSDIR)\$(RECTANGLE).o $(TESTBINDIR)\$(RECTANGLE).exe

#####################################
# for making the point test file
#####################################
point: $(POINT)
	@echo "pointTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(POINT).o' -Destination '$(TESTOBJSDIR)\$(POINT).o' -force"

$(POINT): $(POINT_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_POINT):
	del /Q $(TESTOBJSDIR)\$(POINT).o $(TESTBINDIR)\$(POINT).exe
##############################################################
#						Project Files
##############################################################
project: $(PROJECT)
	@echo "project built!"
	powershell.exe -Command "Move-Item -Path '$(PROJSRCSDIR)\$(PROJECT).o' -Destination '$(PROJOBJSDIR)\$(PROJECT).o' -force"
	powershell.exe -Command "Move-Item -Path '$(OBJSRCDIR)\$(CIRCLEOBJ).o' -Destination '$(PROJOBJSDIR)\$(CIRCLEOBJ).o' -force"
	powershell.exe -Command "Move-Item -Path '$(OBJSRCDIR)\$(POINTOBJ).o' -Destination '$(PROJOBJSDIR)\$(POINTOBJ).o' -force"
	powershell.exe -Command "Move-Item -Path '$(OBJSRCDIR)\$(RECTOBJ).o' -Destination '$(PROJOBJSDIR)\$(RECTOBJ).o' -force"
	powershell.exe -Command "Move-Item -Path '$(OBJSRCDIR)\$(OBJOBJ).o' -Destination '$(PROJOBJSDIR)\$(OBJOBJ).o' -force"
	powershell.exe -Command "Move-Item -Path '$(OBJSRCDIR)\$(VELOCITYOBJ).o' -Destination '$(PROJOBJSDIR)\$(VELOCITYOBJ).o' -force"

$(PROJECT): $(PROJECT_OBJS)
	$(CC) $(CFLAGS) -o $(PROJBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PROJECT):
	del /Q $(PROJOBJSDIR)\$(PROJECT).o $(PROJBINDIR)\$(PROJECT).exe
	del /Q $(PROJOBJSDIR)\$(CIRCLEOBJ).o
	del /Q $(PROJOBJSDIR)\$(POINTOBJ).o
	del /Q $(PROJOBJSDIR)\$(RECTOBJ).o
	del /Q $(PROJOBJSDIR)\$(OBJOBJ).o
	del /Q $(PROJOBJSDIR)\$(VELOCITYOBJ).o