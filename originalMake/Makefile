##################################
 # codecompiler flags
##################################
PROJECTDIR = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

ifeq ($(OS),Windows_NT)
	CC = g++
	CFLAGS = -std=c++17 -Wall -Wextra -I$(PROJECTDIR)dependancies/glm/glm -I/C:/Users/seth1/OneDrive/Documents/vcpkg/installed/x86-windows/include/liblas
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -L$(PROJECTDIR)dependancies/glm -Wl,-rpath=$(PROJECTDIR)dependancies/glm -L/C:\Users\seth1\OneDrive\Documents\vcpkg\installed\x86-windows\lib -lglm_shared -llas
else
	CC = g++
	CFLAGS = -std=c++17 -Wall -Wextra
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -lglm
endif

TESTSRCSDIR = .\tests\src
TESTOBJSDIR = .\tests\bin\objs
TESTBINDIR = .\tests\bin

PROJSRCSDIR = .\src
PROJOBJSDIR = .\bin\objs
PROJBINDIR = .\bin

OBJCPPDIR = $(PROJSRCSDIR)\objects\functions
OBJHPPDIR = $(PROJSRCSDIR)\objects\definitions
FILEDIR = $(PROJSRCSDIR)\fileHandlers
UIDIR = $(PROJSRCSDIR)\canvas\uiHandlers

CIRCLEOBJ = circle
POINTOBJ = point
RECTOBJ = rectangle
OBJOBJ = object
VELOCITYOBJ = velocity
FILEWRITER = outputProtocol
FILEREADER = inputProtocol
UIDRAW = billboard

BASEOBJS = $(OBJCPPDIR)\$(CIRCLEOBJ).cpp $(OBJCPPDIR)\$(POINTOBJ).cpp $(OBJCPPDIR)\$(RECTOBJ).cpp $(OBJCPPDIR)\$(OBJOBJ).cpp $(OBJCPPDIR)\$(VELOCITYOBJ).cpp

GLFWCIRCLEOBJ = GLFWcircle
GLFWRECTOBJ = GLFWrectangle
GLFWOBJECT = GLFWobject

GLFWOBJS = $(OBJCPPDIR)\$(GLFWCIRCLEOBJ).cpp $(OBJCPPDIR)\$(GLFWRECTOBJ).cpp 

GRAVCIRCLEOBJ = gravityGLFWcircle
GRAVRECTOBJ = gravityGLFWrectangle


GRAVITYOBJS = $(OBJHPPDIR)\$(GRAVCIRCLEOBJ).hpp $(OBJHPPDIR)\$(GRAVRECTOBJ).hpp

MASTEROBJS = $(BASEOBJS) $(GLFWOBJS) $(GRAVITYOBJS)

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

MACHINE = MLTest
MACHINE_SRCS = $(TESTSRCSDIR)\$(MACHINE).cpp
MACHINE_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(MACHINE_SRCS:.cpp=.o))

LAS = lasTest
LAS_SRCS = $(TESTSRCSDIR)\$(LAS).cpp
LAS_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(LAS_SRCS:.cpp=.o))

BILLBOARD = billboardTest
BILLBOARD_SRCS = $(TESTSRCSDIR)\$(BILLBOARD).cpp
BILLBOARD_OBJS = $(patsubst $(TESTSRCSDIR)\%.cpp, $(TESTOBJSDIR)\%.o, $(BILLBOARD_SRCS:.cpp=.o))
#####################################
 # clean test declaration prototypes
#####################################
CLEAN_GLUTTEST = clean_glutTest
CLEAN_COLLISIONS = clean_collisions
CLEAN_PLANETS = clean_planets
CLEAN_CIRCLE = clean_circle
CLEAN_RECTANGLE = clean_rectangle
CLEAN_POINT = clean_point
CLEAN_MACHINE = clean_machine
CLEAN_LAS = clean_las
CLEAN_BILLBOARD = clean_billboard

#####################################
 # project declaration prototypes
#####################################
PROJECT = main
PROJECT_SRCS = $(PROJSRCSDIR)\$(PROJECT).cpp $(OBJCPPDIR)\$(POINTOBJ).cpp $(OBJHPPDIR)\$(GLFWOBJECT).hpp $(FILEDIR)\$(FILEWRITER).hpp $(FILEDIR)\$(FILEREADER).hpp $(UIDIR)\$(UIDRAW).hpp
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

tests: glut collisions planets circle rectangle point las

clean_tests: $(CLEAN_GLUTTEST) $(CLEAN_COLLISIONS) $(CLEAN_PLANETS) $(CLEAN_CIRCLE) $(CLEAN_RECTANGLE) $(CLEAN_POINT) $(CLEAN_GRAVITY)


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

#####################################
# for making the Machine learning test file
#####################################
machine: $(MACHINE)
	@echo "machineTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(MACHINE).o' -Destination '$(TESTOBJSDIR)\$(MACHINE).o' -force"

$(MACHINE): $(MACHINE_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_MACHINE):
	del /Q $(TESTOBJSDIR)\$(MACHINE).o $(TESTBINDIR)\$(MACHINE).exe

#####################################
# for making the LAS/LAZ test file
#####################################
las: $(LAS)
	@echo "LAStest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(LAS).o' -Destination '$(TESTOBJSDIR)\$(LAS).o' -force"

$(LAS): $(LAS_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_LAS):
	del /Q $(TESTOBJSDIR)\$(LAS).o $(TESTBINDIR)\$(LAS).exe

#####################################
# for making the billboard test file
#####################################
billboard: $(BILLBOARD)
	@echo "billboard test built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(BILLBOARD).o' -Destination '$(TESTOBJSDIR)\$(BILLBOARD).o' -force"

$(BILLBOARD): $(BILLBOARD_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_BILLBOARD):
	del /Q $(TESTOBJSDIR)\$(BILLBOARD).o $(TESTBINDIR)\$(BILLBOARD).exe
##############################################################
#						Project Files
##############################################################
project: $(PROJECT)
	@powershell.exe -Command "Move-Item -Path '$(PROJSRCSDIR)\$(PROJECT).o' -Destination '$(PROJOBJSDIR)\$(PROJECT).o' -force"
	@powershell.exe -Command "Move-Item -Path '$(OBJCPPDIR)\$(POINTOBJ).o' -Destination '$(PROJOBJSDIR)\$(POINTOBJ).o' -force"
	@echo "project built!"
	@powershell.exe -Command "date"

$(PROJECT): $(PROJECT_OBJS)
	$(CC) $(CFLAGS) -o $(PROJBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PROJECT):
	del /Q $(PROJOBJSDIR)\$(PROJECT).o $(PROJBINDIR)\$(PROJECT).exe
	del /Q $(PROJOBJSDIR)\$(POINTOBJ).o