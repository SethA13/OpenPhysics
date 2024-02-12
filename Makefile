# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/nix/store/hkhmxs4n1agpdpyamlh2b78pm9wch0br-cmake-3.27.9/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/nix/store/hkhmxs4n1agpdpyamlh2b78pm9wch0br-cmake-3.27.9/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/seth/Documents/OpenPhysics/CMakeFiles /home/seth/Documents/OpenPhysics//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/seth/Documents/OpenPhysics/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named glutTest

# Build rule for target.
glutTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 glutTest
.PHONY : glutTest

# fast build rule for target.
glutTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/glutTest.dir/build.make CMakeFiles/glutTest.dir/build
.PHONY : glutTest/fast

#=============================================================================
# Target rules for targets named collisionTest

# Build rule for target.
collisionTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 collisionTest
.PHONY : collisionTest

# fast build rule for target.
collisionTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/collisionTest.dir/build.make CMakeFiles/collisionTest.dir/build
.PHONY : collisionTest/fast

#=============================================================================
# Target rules for targets named planetTest

# Build rule for target.
planetTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 planetTest
.PHONY : planetTest

# fast build rule for target.
planetTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/planetTest.dir/build.make CMakeFiles/planetTest.dir/build
.PHONY : planetTest/fast

#=============================================================================
# Target rules for targets named circleTest

# Build rule for target.
circleTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 circleTest
.PHONY : circleTest

# fast build rule for target.
circleTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/circleTest.dir/build.make CMakeFiles/circleTest.dir/build
.PHONY : circleTest/fast

#=============================================================================
# Target rules for targets named rectangleTest

# Build rule for target.
rectangleTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 rectangleTest
.PHONY : rectangleTest

# fast build rule for target.
rectangleTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/rectangleTest.dir/build.make CMakeFiles/rectangleTest.dir/build
.PHONY : rectangleTest/fast

#=============================================================================
# Target rules for targets named pointTest

# Build rule for target.
pointTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 pointTest
.PHONY : pointTest

# fast build rule for target.
pointTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/pointTest.dir/build.make CMakeFiles/pointTest.dir/build
.PHONY : pointTest/fast

#=============================================================================
# Target rules for targets named openPhysics

# Build rule for target.
openPhysics: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 openPhysics
.PHONY : openPhysics

# fast build rule for target.
openPhysics/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/build
.PHONY : openPhysics/fast

#=============================================================================
# Target rules for targets named clean_all

# Build rule for target.
clean_all: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean_all
.PHONY : clean_all

# fast build rule for target.
clean_all/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clean_all.dir/build.make CMakeFiles/clean_all.dir/build
.PHONY : clean_all/fast

#=============================================================================
# Target rules for targets named clean_tests

# Build rule for target.
clean_tests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean_tests
.PHONY : clean_tests

# fast build rule for target.
clean_tests/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clean_tests.dir/build.make CMakeFiles/clean_tests.dir/build
.PHONY : clean_tests/fast

#=============================================================================
# Target rules for targets named clean_project

# Build rule for target.
clean_project: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean_project
.PHONY : clean_project

# fast build rule for target.
clean_project/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clean_project.dir/build.make CMakeFiles/clean_project.dir/build
.PHONY : clean_project/fast

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/objects/functions/point.o: src/objects/functions/point.cpp.o
.PHONY : src/objects/functions/point.o

# target to build an object file
src/objects/functions/point.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/src/objects/functions/point.cpp.o
.PHONY : src/objects/functions/point.cpp.o

src/objects/functions/point.i: src/objects/functions/point.cpp.i
.PHONY : src/objects/functions/point.i

# target to preprocess a source file
src/objects/functions/point.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/src/objects/functions/point.cpp.i
.PHONY : src/objects/functions/point.cpp.i

src/objects/functions/point.s: src/objects/functions/point.cpp.s
.PHONY : src/objects/functions/point.s

# target to generate assembly for a file
src/objects/functions/point.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/openPhysics.dir/build.make CMakeFiles/openPhysics.dir/src/objects/functions/point.cpp.s
.PHONY : src/objects/functions/point.cpp.s

tests/src/circleTest.o: tests/src/circleTest.cpp.o
.PHONY : tests/src/circleTest.o

# target to build an object file
tests/src/circleTest.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/circleTest.dir/build.make CMakeFiles/circleTest.dir/tests/src/circleTest.cpp.o
.PHONY : tests/src/circleTest.cpp.o

tests/src/circleTest.i: tests/src/circleTest.cpp.i
.PHONY : tests/src/circleTest.i

# target to preprocess a source file
tests/src/circleTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/circleTest.dir/build.make CMakeFiles/circleTest.dir/tests/src/circleTest.cpp.i
.PHONY : tests/src/circleTest.cpp.i

tests/src/circleTest.s: tests/src/circleTest.cpp.s
.PHONY : tests/src/circleTest.s

# target to generate assembly for a file
tests/src/circleTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/circleTest.dir/build.make CMakeFiles/circleTest.dir/tests/src/circleTest.cpp.s
.PHONY : tests/src/circleTest.cpp.s

tests/src/collisionTest.o: tests/src/collisionTest.cpp.o
.PHONY : tests/src/collisionTest.o

# target to build an object file
tests/src/collisionTest.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/collisionTest.dir/build.make CMakeFiles/collisionTest.dir/tests/src/collisionTest.cpp.o
.PHONY : tests/src/collisionTest.cpp.o

tests/src/collisionTest.i: tests/src/collisionTest.cpp.i
.PHONY : tests/src/collisionTest.i

# target to preprocess a source file
tests/src/collisionTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/collisionTest.dir/build.make CMakeFiles/collisionTest.dir/tests/src/collisionTest.cpp.i
.PHONY : tests/src/collisionTest.cpp.i

tests/src/collisionTest.s: tests/src/collisionTest.cpp.s
.PHONY : tests/src/collisionTest.s

# target to generate assembly for a file
tests/src/collisionTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/collisionTest.dir/build.make CMakeFiles/collisionTest.dir/tests/src/collisionTest.cpp.s
.PHONY : tests/src/collisionTest.cpp.s

tests/src/glutTest.o: tests/src/glutTest.cpp.o
.PHONY : tests/src/glutTest.o

# target to build an object file
tests/src/glutTest.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/glutTest.dir/build.make CMakeFiles/glutTest.dir/tests/src/glutTest.cpp.o
.PHONY : tests/src/glutTest.cpp.o

tests/src/glutTest.i: tests/src/glutTest.cpp.i
.PHONY : tests/src/glutTest.i

# target to preprocess a source file
tests/src/glutTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/glutTest.dir/build.make CMakeFiles/glutTest.dir/tests/src/glutTest.cpp.i
.PHONY : tests/src/glutTest.cpp.i

tests/src/glutTest.s: tests/src/glutTest.cpp.s
.PHONY : tests/src/glutTest.s

# target to generate assembly for a file
tests/src/glutTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/glutTest.dir/build.make CMakeFiles/glutTest.dir/tests/src/glutTest.cpp.s
.PHONY : tests/src/glutTest.cpp.s

tests/src/planetTest.o: tests/src/planetTest.cpp.o
.PHONY : tests/src/planetTest.o

# target to build an object file
tests/src/planetTest.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/planetTest.dir/build.make CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.o
.PHONY : tests/src/planetTest.cpp.o

tests/src/planetTest.i: tests/src/planetTest.cpp.i
.PHONY : tests/src/planetTest.i

# target to preprocess a source file
tests/src/planetTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/planetTest.dir/build.make CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.i
.PHONY : tests/src/planetTest.cpp.i

tests/src/planetTest.s: tests/src/planetTest.cpp.s
.PHONY : tests/src/planetTest.s

# target to generate assembly for a file
tests/src/planetTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/planetTest.dir/build.make CMakeFiles/planetTest.dir/tests/src/planetTest.cpp.s
.PHONY : tests/src/planetTest.cpp.s

tests/src/pointTest.o: tests/src/pointTest.cpp.o
.PHONY : tests/src/pointTest.o

# target to build an object file
tests/src/pointTest.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/pointTest.dir/build.make CMakeFiles/pointTest.dir/tests/src/pointTest.cpp.o
.PHONY : tests/src/pointTest.cpp.o

tests/src/pointTest.i: tests/src/pointTest.cpp.i
.PHONY : tests/src/pointTest.i

# target to preprocess a source file
tests/src/pointTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/pointTest.dir/build.make CMakeFiles/pointTest.dir/tests/src/pointTest.cpp.i
.PHONY : tests/src/pointTest.cpp.i

tests/src/pointTest.s: tests/src/pointTest.cpp.s
.PHONY : tests/src/pointTest.s

# target to generate assembly for a file
tests/src/pointTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/pointTest.dir/build.make CMakeFiles/pointTest.dir/tests/src/pointTest.cpp.s
.PHONY : tests/src/pointTest.cpp.s

tests/src/rectangleTest.o: tests/src/rectangleTest.cpp.o
.PHONY : tests/src/rectangleTest.o

# target to build an object file
tests/src/rectangleTest.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/rectangleTest.dir/build.make CMakeFiles/rectangleTest.dir/tests/src/rectangleTest.cpp.o
.PHONY : tests/src/rectangleTest.cpp.o

tests/src/rectangleTest.i: tests/src/rectangleTest.cpp.i
.PHONY : tests/src/rectangleTest.i

# target to preprocess a source file
tests/src/rectangleTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/rectangleTest.dir/build.make CMakeFiles/rectangleTest.dir/tests/src/rectangleTest.cpp.i
.PHONY : tests/src/rectangleTest.cpp.i

tests/src/rectangleTest.s: tests/src/rectangleTest.cpp.s
.PHONY : tests/src/rectangleTest.s

# target to generate assembly for a file
tests/src/rectangleTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/rectangleTest.dir/build.make CMakeFiles/rectangleTest.dir/tests/src/rectangleTest.cpp.s
.PHONY : tests/src/rectangleTest.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... clean_all"
	@echo "... clean_project"
	@echo "... clean_tests"
	@echo "... circleTest"
	@echo "... collisionTest"
	@echo "... glutTest"
	@echo "... openPhysics"
	@echo "... planetTest"
	@echo "... pointTest"
	@echo "... rectangleTest"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/objects/functions/point.o"
	@echo "... src/objects/functions/point.i"
	@echo "... src/objects/functions/point.s"
	@echo "... tests/src/circleTest.o"
	@echo "... tests/src/circleTest.i"
	@echo "... tests/src/circleTest.s"
	@echo "... tests/src/collisionTest.o"
	@echo "... tests/src/collisionTest.i"
	@echo "... tests/src/collisionTest.s"
	@echo "... tests/src/glutTest.o"
	@echo "... tests/src/glutTest.i"
	@echo "... tests/src/glutTest.s"
	@echo "... tests/src/planetTest.o"
	@echo "... tests/src/planetTest.i"
	@echo "... tests/src/planetTest.s"
	@echo "... tests/src/pointTest.o"
	@echo "... tests/src/pointTest.i"
	@echo "... tests/src/pointTest.s"
	@echo "... tests/src/rectangleTest.o"
	@echo "... tests/src/rectangleTest.i"
	@echo "... tests/src/rectangleTest.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

