##################################
 # codecompiler flags
##################################
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32

PROJECTDIR = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

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
#####################################
 # clean test declaration prototypes
#####################################
CLEAN_GLUTTEST = clean_glutTest
CLEAN_COLLISIONS = clean_collisions
CLEAN_PLANETS = clean_planets



#########################################################################
 # 							Task Declarations
 #		all:
 #			compile both the glut test and the collisions test
 #		clean_all:
 #			delete all compiled files
 #		glutTest:
 #			compile glutTest
 # 		clean_glutTest:
 #			delete compilation files for glutTest
 # 		collisions:
 # 			compile collisions
 # 		clean_collisions:
 # 			delete compilation files for collisions 
#########################################################################
tests: glut collisions planets

clean_tests: $(CLEAN_GLUTTEST) $(CLEAN_COLLISIONS) $(CLEAN_PLANETS)

#####################################
# for making the glut test file
#####################################
glut: $(GLUTTEST)
	@echo "glutTest built!"
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(GLUTTEST).o' -Destination '$(TESTOBJSDIR)\$(GLUTTEST).o'"

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
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(COLLISIONS).o' -Destination '$(TESTOBJSDIR)\$(COLLISIONS).o'"

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
	powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)\$(PLANETS).o' -Destination '$(TESTOBJSDIR)\$(PLANETS).o'"

$(PLANETS): $(PLANETS_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)\$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PLANETS):
	del /Q $(TESTOBJSDIR)\$(PLANETS).o $(TESTBINDIR)\$(PLANETS).exe