CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lglew32

TARGET = test

SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
