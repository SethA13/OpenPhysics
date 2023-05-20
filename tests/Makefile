##################################
 # codecompiler flags
##################################
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32

##################################
 # task declaration prototypes
##################################
GLUTTEST = glutTest
GLUTTEST_SRCS = glutTest.cpp
GLUTTEST_OBJS = $(GLUTTEST_SRCS:.cpp=.o)

COLLISIONS = collisionTest
COLLISIONS_SRCS = collisionTest.cpp
COLLISIONS_OBJS = $(COLLISIONS_SRCS:.cpp=.o)
##################################
 # clean declaration prototypes
##################################
CLEAN_GLUTTEST = clean_glutTest
CLEAN_COLLISIONS = clean_collisions



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
all: $(GLUTTEST) $(COLLISIONS)

clean_all: $(CLEAN_GLUTTEST) $(CLEAN_COLLISIONS)

#####################################
# for making the glut test file
#####################################
glut: $(GLUTTEST)

$(GLUTTEST): $(GLUTTEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_GLUTTEST):
	del -f $(GLUTTEST_OBJS) $(GLUTTEST).exe

#####################################
# for making the collisions test file
#####################################
collisions: $(COLLISIONS)

$(COLLISIONS): $(COLLISIONS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLEAN_COLLISIONS):
	del -f collisionTest.o $(COLLISIONS).exe