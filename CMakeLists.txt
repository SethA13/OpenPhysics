cmake_minimum_required(VERSION 3.15)
project(OpenPhysics)

# Set C++ standard and compile flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Define the paths to your dependencies
set(GLM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependancies/glm-0.9.7.1)

# Add the glm library as a subdirectory
add_subdirectory(${GLM_DIR})

# Create an executable for your main project
add_executable(main src/main.cpp)

# Specify the include directories
target_include_directories(main PRIVATE ${GLM_DIR})

# Link the necessary libraries
target_link_libraries(main PRIVATE opengl32 glu32 freeglut glew32 glfw3 glm)

# Add additional executables for your tests
add_executable(glutTest tests/src/glutTest.cpp)
target_include_directories(glutTest PRIVATE ${GLM_DIR})
target_link_libraries(glutTest PRIVATE opengl32 glu32 freeglut glew32 glfw3 glm)

add_executable(collisionTest tests/src/collisionTest.cpp)
target_include_directories(collisionTest PRIVATE ${GLM_DIR})
target_link_libraries(collisionTest PRIVATE opengl32 glu32 freeglut glew32 glfw3 glm)

add_executable(planetTest tests/src/planetTest.cpp)
target_include_directories(planetTest PRIVATE ${GLM_DIR})
target_link_libraries(planetTest PRIVATE opengl32 glu32 freeglut glew32 glfw3 glm)
