# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wyq/Project/LLM-infra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wyq/Project/LLM-infra/build

# Include any dependencies generated for this target.
include CMakeFiles/matrix_multiplication.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/matrix_multiplication.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/matrix_multiplication.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrix_multiplication.dir/flags.make

CMakeFiles/matrix_multiplication.dir/main.cpp.o: CMakeFiles/matrix_multiplication.dir/flags.make
CMakeFiles/matrix_multiplication.dir/main.cpp.o: ../main.cpp
CMakeFiles/matrix_multiplication.dir/main.cpp.o: CMakeFiles/matrix_multiplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyq/Project/LLM-infra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matrix_multiplication.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/matrix_multiplication.dir/main.cpp.o -MF CMakeFiles/matrix_multiplication.dir/main.cpp.o.d -o CMakeFiles/matrix_multiplication.dir/main.cpp.o -c /home/wyq/Project/LLM-infra/main.cpp

CMakeFiles/matrix_multiplication.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrix_multiplication.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wyq/Project/LLM-infra/main.cpp > CMakeFiles/matrix_multiplication.dir/main.cpp.i

CMakeFiles/matrix_multiplication.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrix_multiplication.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wyq/Project/LLM-infra/main.cpp -o CMakeFiles/matrix_multiplication.dir/main.cpp.s

# Object files for target matrix_multiplication
matrix_multiplication_OBJECTS = \
"CMakeFiles/matrix_multiplication.dir/main.cpp.o"

# External object files for target matrix_multiplication
matrix_multiplication_EXTERNAL_OBJECTS =

Debug/matrix_multiplication: CMakeFiles/matrix_multiplication.dir/main.cpp.o
Debug/matrix_multiplication: CMakeFiles/matrix_multiplication.dir/build.make
Debug/matrix_multiplication: CMakeFiles/matrix_multiplication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wyq/Project/LLM-infra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Debug/matrix_multiplication"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrix_multiplication.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matrix_multiplication.dir/build: Debug/matrix_multiplication
.PHONY : CMakeFiles/matrix_multiplication.dir/build

CMakeFiles/matrix_multiplication.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrix_multiplication.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrix_multiplication.dir/clean

CMakeFiles/matrix_multiplication.dir/depend:
	cd /home/wyq/Project/LLM-infra/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wyq/Project/LLM-infra /home/wyq/Project/LLM-infra /home/wyq/Project/LLM-infra/build /home/wyq/Project/LLM-infra/build /home/wyq/Project/LLM-infra/build/CMakeFiles/matrix_multiplication.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matrix_multiplication.dir/depend

