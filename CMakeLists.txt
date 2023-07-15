cmake_minimum_required(VERSION 3.5)
project(openPhysics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project directory
get_filename_component(PROJECTDIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)

# Check the operating system
if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Set include directories
include_directories(${PROJECTDIR}/dependancies/glm/glm)

# Set libraries
if(WIN32)
	set(LIBRARIES opengl32 glu32 freeglut glew32 glfw3)
else()
	set(LIBRARIES GL GLU glut GLEW glfw3)
endif()

# Set source files
set(TESTSRCSDIR tests/src)
set(TESTOBJSDIR tests/bin/objs)
set(TESTBINDIR tests/bin)

set(PROJSRCSDIR src)
set(PROJOBJSDIR bin/objs)
set(PROJBINDIR bin)

set(OBJCPPDIR ${PROJSRCSDIR}/objects/functions)
set(OBJHPPDIR ${PROJSRCSDIR}/objects/definitions)
set(FILEDIR ${PROJSRCSDIR}/fileHandlers)

set(CIRCLEOBJ circle)
set(POINTOBJ point)
set(RECTOBJ rectangle)
set(OBJOBJ object)
set(VELOCITYOBJ velocity)
set(FILEWRITER outputProtocol)
set(FILEREADER inputProtocol)

set(BASEOBJS ${OBJCPPDIR}/${CIRCLEOBJ}.cpp ${OBJCPPDIR}/${POINTOBJ}.cpp ${OBJCPPDIR}/${RECTOBJ}.cpp ${OBJCPPDIR}/${OBJOBJ}.cpp ${OBJCPPDIR}/${VELOCITYOBJ}.cpp)

set(GLFWCIRCLEOBJ GLFWcircle)
set(GLFWRECTOBJ GLFWrectangle)
set(GLFWOBJECT GLFWobject)

set(GLFWOBJS ${OBJCPPDIR}/${GLFWCIRCLEOBJ}.cpp ${OBJCPPDIR}/${GLFWRECTOBJ}.cpp)

set(GRAVCIRCLEOBJ gravityGLFWcircle)
set(GRAVRECTOBJ gravityGLFWrectangle)

set(GRAVITYOBJS ${OBJHPPDIR}/${GRAVCIRCLEOBJ}.hpp ${OBJHPPDIR}/${GRAVRECTOBJ}.hpp)

set(MASTEROBJS ${BASEOBJS} ${GLFWOBJS} ${GRAVITYOBJS})

# Test declaration prototypes
set(GLUTTEST glutTest)
set(GLUTTEST_SRCS ${TESTSRCSDIR}/${GLUTTEST}.cpp)
set(GLUTTEST_OBJS ${TESTOBJSDIR}/glutTest.o)

set(COLLISIONS collisionTest)
set(COLLISIONS_SRCS ${TESTSRCSDIR}/${COLLISIONS}.cpp)
set(COLLISIONS_OBJS ${TESTOBJSDIR}/collisionTest.o)

set(PLANETS planetTest)
set(PLANETS_SRCS ${TESTSRCSDIR}/${PLANETS}.cpp)
set(PLANETS_OBJS ${TESTOBJSDIR}/planetTest.o)

set(CIRCLE circleTest)
set(CIRCLE_SRCS ${TESTSRCSDIR}/${CIRCLE}.cpp)
set(CIRCLE_OBJS ${TESTOBJSDIR}/circleTest.o)

set(RECTANGLE rectangleTest)
set(RECT_SRCS ${TESTSRCSDIR}/${RECTANGLE}.cpp)
set(RECT_OBJS ${TESTOBJSDIR}/rectangleTest.o)

set(POINT pointTest)
set(POINT_SRCS ${TESTSRCSDIR}/${POINT}.cpp)
set(POINT_OBJS ${TESTOBJSDIR}/pointTest.o)

set(GRAVITY gravityTest)
set(GRAVITY_SRCS ${TESTSRCSDIR}/${GRAVITY}.cpp ${OBJHPPDIR}/${GRAVCIRCLEOBJ}.hpp)
set(GRAVITY_OBJS ${TESTOBJSDIR}/gravityTest.o)

# Main project declaration prototype
set(PROJECT main)
set(PROJECT_SRCS ${PROJSRCSDIR}/${PROJECT}.cpp ${OBJCPPDIR}/${POINTOBJ}.cpp ${OBJHPPDIR}/${GLFWOBJECT}.hpp ${FILEDIR}/${FILEWRITER}.hpp ${FILEDIR}/${FILEREADER}.hpp)
set(PROJECT_OBJS ${PROJOBJSDIR}/${PROJECT}.o)


# Add executable targets
add_executable(${GLUTTEST} ${GLUTTEST_SRCS})
add_executable(${COLLISIONS} ${COLLISIONS_SRCS})
add_executable(${PLANETS} ${PLANETS_SRCS})
add_executable(${CIRCLE} ${CIRCLE_SRCS})
add_executable(${RECTANGLE} ${RECT_SRCS})
add_executable(${POINT} ${POINT_SRCS})
add_executable(${GRAVITY} ${GRAVITY_SRCS})

# Main project executable
add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

# Set the output directories for tests
set_target_properties(${GLUTTEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})
set_target_properties(${COLLISIONS} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})
set_target_properties(${PLANETS} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})
set_target_properties(${CIRCLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})
set_target_properties(${RECTANGLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})
set_target_properties(${POINT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})
set_target_properties(${GRAVITY} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTBINDIR})

# Set the output directories for the project
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJBINDIR})

# Link libraries to tests
target_link_libraries(${GLUTTEST} ${LIBRARIES})
target_link_libraries(${COLLISIONS} ${LIBRARIES})
target_link_libraries(${PLANETS} ${LIBRARIES})
target_link_libraries(${CIRCLE} ${LIBRARIES})
target_link_libraries(${RECTANGLE} ${LIBRARIES})
target_link_libraries(${POINT} ${LIBRARIES})
target_link_libraries(${GRAVITY} ${LIBRARIES})

# Link libraries to the main project
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Clean targets
add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${TESTBINDIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${TESTOBJSDIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJOBJSDIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJBINDIR}
)

add_custom_target(clean_tests
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${TESTBINDIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${TESTOBJSDIR}
)

add_custom_target(clean_project
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJOBJSDIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJBINDIR}
)