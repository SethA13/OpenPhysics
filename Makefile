##################################
 # codecompiler flags
##################################
PROJECTDIR = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

ifeq ($(OS),Windows_NT)
	CC = g++
	CFLAGS = -std=c++11 -Wall -Wextra -I$(PROJECTDIR)dependancies/glm/glm
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -L$(PROJECTDIR)dependancies/glm -Wl,-rpath=$(PROJECTDIR)dependancies/glm -lglm_shared

	SEP = \\

else
	CC = g++
	CFLAGS = -std=c++11 -Wall -Wextra
	LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32 -lglfw3 -lglm

	SEP = /
endif

TESTSRCSDIR = .$(SEP)tests$(SEP)src
TESTOBJSDIR = .$(SEP)tests$(SEP)bin$(SEP)objs
TESTBINDIR = .$(SEP)tests$(SEP)bin
##################################
 # test declaration prototypes
##################################
GLUTTEST = glutTest
GLUTTEST_SRCS = $(TESTSRCSDIR)$(SEP)glutTest.cpp
GLUTTEST_OBJS = $(patsubst $(TESTSRCSDIR)$(SEP)%.cpp, $(TESTOBJSDIR)$(SEP)%.o, $(GLUTTEST_SRCS:.cpp=.o))

COLLISIONS = collisionTest
COLLISIONS_SRCS = $(TESTSRCSDIR)$(SEP)collisionTest.cpp
COLLISIONS_OBJS = $(patsubst $(TESTSRCSDIR)$(SEP)%.cpp, $(TESTOBJSDIR)$(SEP)%.o, $(COLLISIONS_SRCS:.cpp=.o))

PLANETS = planetTest
PLANETS_SRCS = $(TESTSRCSDIR)$(SEP)planetTest.cpp
PLANETS_OBJS = $(patsubst $(TESTSRCSDIR)$(SEP)%.cpp, $(TESTOBJSDIR)$(SEP)%.o, $(PLANETS_SRCS:.cpp=.o))
#####################################
 # clean test declaration prototypes
#####################################
CLEAN_GLUTTEST = clean_glutTest
CLEAN_COLLISIONS = clean_collisions
CLEAN_PLANETS = clean_planets



PROJSRCSDIR = .$(SEP)src
PROJOBJSDIR = .$(SEP)bin$(SEP)objs
PROJBINDIR = .$(SEP)bin
#####################################
 # project declaration prototypes
#####################################
PROJECT = main
PROJECT_SRCS = $(PROJSRCSDIR)$(SEP)main.cpp
PROJECT_OBJS = $(patsubst $(PROJSRCSDIR)$(SEP)%.cpp, $(PROJOBJSDIR)$(SEP)%.o, $(PROJECT_SRCS:.cpp=.o))
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

tests: glut collisions planets

clean_tests: $(CLEAN_GLUTTEST) $(CLEAN_COLLISIONS) $(CLEAN_PLANETS)


##############################################################
#						Test Files
##############################################################
#####################################
# for making the glut test file
#####################################
glut: $(GLUTTEST)
	@echo "glutTest built!"
	ifeq ($(OS),Windows_NT)
		powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)$(SEP)$(GLUTTEST).o' -Destination '$(TESTOBJSDIR)$(SEP)$(GLUTTEST).o' -force"
	else
		mv $(TESTSRCSDIR)$(SEP)$(GLUTTEST).o $(TESTOBJSDIR)$(SEP)$(GLUTTEST).o
	endif

$(GLUTTEST): $(GLUTTEST_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)$(SEP)$@ $^ $(LDFLAGS)

$(TESTOBJSDIR)$(SEP)%.o: $(TESTSRCSDIR)$(SEP)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_GLUTTEST):
	ifeq ($(OS),Windows_NT)
		del /Q $(TESTOBJSDIR)$(SEP)$(GLUTTEST).o $(TESTBINDIR)$(SEP)$(GLUTTEST).exe
	else
		rm -f $(TESTOBJSDIR)$(SEP)$(GLUTTEST).o $(TESTBINDIR)$(SEP)$(GLUTTEST)
	endif
#####################################
# for making the collisions test file
#####################################
collisions: $(COLLISIONS)
	@echo "collisionTest built!"
	ifeq ($(OS),Windows_NT)
		powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)$(SEP)$(COLLISIONS).o' -Destination '$(TESTOBJSDIR)$(SEP)$(COLLISIONS).o' -force"
	else

	endif

$(COLLISIONS): $(COLLISIONS_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)$(SEP)$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_COLLISIONS):
	ifeq ($(OS),Windows_NT)
		del /Q $(TESTOBJSDIR)$(SEP)$(COLLISIONS).o $(TESTBINDIR)$(SEP)$(COLLISIONS).exe
	else

	endif
#####################################
# for making the planets test file
#####################################
planets: $(PLANETS)
	@echo "planetTest built!"
	ifeq ($(OS),Windows_NT)
		powershell.exe -Command "Move-Item -Path '$(TESTSRCSDIR)$(SEP)$(PLANETS).o' -Destination '$(TESTOBJSDIR)$(SEP)$(PLANETS).o' -force"
	else

	endif
$(PLANETS): $(PLANETS_OBJS)
	$(CC) $(CFLAGS) -o $(TESTBINDIR)$(SEP)$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PLANETS):
	ifeq ($(OS),Windows_NT)
		del /Q $(TESTOBJSDIR)$(SEP)$(PLANETS).o $(TESTBINDIR)$(SEP)$(PLANETS).exe
	else

##############################################################
#						Project Files
##############################################################
project: $(PROJECT)
	@echo "project built!"
	@echo "$(PROJSRCSDIR)\$(PROJECT).o"
	ifeq ($(OS),Windows_NT)
		powershell.exe -Command "Move-Item -Path '$(PROJSRCSDIR)$(PROJECT).o' -Destination '$(PROJOBJSDIR)$(PROJECT).o' -force"
	else
		mv $(PROJSRCSDIR)$(SEP)$(PROJECT).o $(TESTOBJSDIR)/$(GLUTTEST).o
	endif
$(PROJECT): $(PROJECT_OBJS)
	$(CC) $(CFLAGS) -o $(PROJBINDIR)$(SEP)$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_PROJECT):
	ifeq ($(OS),Windows_NT)
		del /Q $(PROJOBJSDIR)$(SEP)$(PROJECT).o $(PROJBINDIR)$(SEP)$(PROJECT).exe
	else
		
	endif