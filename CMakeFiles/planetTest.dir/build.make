# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /nix/store/hkhmxs4n1agpdpyamlh2b78pm9wch0br-cmake-3.27.9/bin/cmake

# The command to remove a file.
RM = /nix/store/hkhmxs4n1agpdpyamlh2b78pm9wch0br-cmake-3.27.9/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seth/Documents/OpenPhysics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seth/Documents/OpenPhysics

# Include any dependencies generated for this target.
include CMakeFiles/planetTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/planetTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/planetTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/planetTest.dir/flags.make

CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o: CMakeFiles/planetTest.dir/flags.make
CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o: tests/src/planetTest.cpp
CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o: CMakeFiles/planetTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/seth/Documents/OpenPhysics/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o"
	/nix/store/4cjqvbp1jbkps185wl8qnbjpf8bdy8j9-gcc-wrapper-13.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o -MF CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o.d -o CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o -c /home/seth/Documents/OpenPhysics/tests/src/planetTest.cpp

CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.i"
	/nix/store/4cjqvbp1jbkps185wl8qnbjpf8bdy8j9-gcc-wrapper-13.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seth/Documents/OpenPhysics/tests/src/planetTest.cpp > CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.i

CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.s"
	/nix/store/4cjqvbp1jbkps185wl8qnbjpf8bdy8j9-gcc-wrapper-13.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seth/Documents/OpenPhysics/tests/src/planetTest.cpp -o CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.s

# Object files for target planetTest
planetTest_OBJECTS = \
"CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o"

# External object files for target planetTest
planetTest_EXTERNAL_OBJECTS =

tests/bin/planetTest: CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o
tests/bin/planetTest: CMakeFiles/planetTest.dir/build.make
tests/bin/planetTest: CMakeFiles/planetTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/seth/Documents/OpenPhysics/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tests/bin/planetTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/planetTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/planetTest.dir/build: tests/bin/planetTest
.PHONY : CMakeFiles/planetTest.dir/build

CMakeFiles/planetTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/planetTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/planetTest.dir/clean

CMakeFiles/planetTest.dir/depend:
	cd /home/seth/Documents/OpenPhysics && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seth/Documents/OpenPhysics /home/seth/Documents/OpenPhysics /home/seth/Documents/OpenPhysics /home/seth/Documents/OpenPhysics /home/seth/Documents/OpenPhysics/CMakeFiles/planetTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/planetTest.dir/depend

