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
CMAKE_SOURCE_DIR = /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafal/Desktop/UWr/PARO/wspolrzedne/build

# Include any dependencies generated for this target.
include CMakeFiles/przekazywanie_przez_kolejke.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/przekazywanie_przez_kolejke.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/przekazywanie_przez_kolejke.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/przekazywanie_przez_kolejke.dir/flags.make

CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o: CMakeFiles/przekazywanie_przez_kolejke.dir/flags.make
CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o: /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania/przekazywanie_przez_kolejke.cpp
CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o: CMakeFiles/przekazywanie_przez_kolejke.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafal/Desktop/UWr/PARO/wspolrzedne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o -MF CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o.d -o CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o -c /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania/przekazywanie_przez_kolejke.cpp

CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania/przekazywanie_przez_kolejke.cpp > CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.i

CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania/przekazywanie_przez_kolejke.cpp -o CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.s

# Object files for target przekazywanie_przez_kolejke
przekazywanie_przez_kolejke_OBJECTS = \
"CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o"

# External object files for target przekazywanie_przez_kolejke
przekazywanie_przez_kolejke_EXTERNAL_OBJECTS =

przekazywanie_przez_kolejke: CMakeFiles/przekazywanie_przez_kolejke.dir/przekazywanie_przez_kolejke.cpp.o
przekazywanie_przez_kolejke: CMakeFiles/przekazywanie_przez_kolejke.dir/build.make
przekazywanie_przez_kolejke: external/libexternal.a
przekazywanie_przez_kolejke: CMakeFiles/przekazywanie_przez_kolejke.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafal/Desktop/UWr/PARO/wspolrzedne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable przekazywanie_przez_kolejke"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/przekazywanie_przez_kolejke.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/przekazywanie_przez_kolejke.dir/build: przekazywanie_przez_kolejke
.PHONY : CMakeFiles/przekazywanie_przez_kolejke.dir/build

CMakeFiles/przekazywanie_przez_kolejke.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/przekazywanie_przez_kolejke.dir/cmake_clean.cmake
.PHONY : CMakeFiles/przekazywanie_przez_kolejke.dir/clean

CMakeFiles/przekazywanie_przez_kolejke.dir/depend:
	cd /home/rafal/Desktop/UWr/PARO/wspolrzedne/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania /home/rafal/Desktop/UWr/PARO/wspolrzedne/zadania /home/rafal/Desktop/UWr/PARO/wspolrzedne/build /home/rafal/Desktop/UWr/PARO/wspolrzedne/build /home/rafal/Desktop/UWr/PARO/wspolrzedne/build/CMakeFiles/przekazywanie_przez_kolejke.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/przekazywanie_przez_kolejke.dir/depend

