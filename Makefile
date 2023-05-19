CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32

TEST = test
COLLISIONS = collisionTest

TEST_SRCS = test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

COLLISIONS_SRCS = collisionTest.cpp collisions.h
COLLISIONS_OBJS = $(COLLISIONS_SRCS:.cpp=.o)

# for making the base test file
test: $(TEST)

$(TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean_test:
	del -f $(TEST_OBJS) $(TEST).exe


# for making the collisions test file
collisions: $(COLLISIONS)

$(COLLISIONS): $(COLLISIONS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean_test:
	del -f $(COLLISIONS_OBJS) $(COLLISIONS).exe