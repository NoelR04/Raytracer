# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build

# Include any dependencies generated for this target.
include CMakeFiles/raytracer.cc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raytracer.cc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raytracer.cc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raytracer.cc.dir/flags.make

CMakeFiles/raytracer.cc.dir/codegen:
.PHONY : CMakeFiles/raytracer.cc.dir/codegen

CMakeFiles/raytracer.cc.dir/raytracer.cc.o: CMakeFiles/raytracer.cc.dir/flags.make
CMakeFiles/raytracer.cc.dir/raytracer.cc.o: /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/raytracer.cc
CMakeFiles/raytracer.cc.dir/raytracer.cc.o: CMakeFiles/raytracer.cc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raytracer.cc.dir/raytracer.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytracer.cc.dir/raytracer.cc.o -MF CMakeFiles/raytracer.cc.dir/raytracer.cc.o.d -o CMakeFiles/raytracer.cc.dir/raytracer.cc.o -c /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/raytracer.cc

CMakeFiles/raytracer.cc.dir/raytracer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raytracer.cc.dir/raytracer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/raytracer.cc > CMakeFiles/raytracer.cc.dir/raytracer.cc.i

CMakeFiles/raytracer.cc.dir/raytracer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raytracer.cc.dir/raytracer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/raytracer.cc -o CMakeFiles/raytracer.cc.dir/raytracer.cc.s

CMakeFiles/raytracer.cc.dir/math.cc.o: CMakeFiles/raytracer.cc.dir/flags.make
CMakeFiles/raytracer.cc.dir/math.cc.o: /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/math.cc
CMakeFiles/raytracer.cc.dir/math.cc.o: CMakeFiles/raytracer.cc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raytracer.cc.dir/math.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytracer.cc.dir/math.cc.o -MF CMakeFiles/raytracer.cc.dir/math.cc.o.d -o CMakeFiles/raytracer.cc.dir/math.cc.o -c /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/math.cc

CMakeFiles/raytracer.cc.dir/math.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raytracer.cc.dir/math.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/math.cc > CMakeFiles/raytracer.cc.dir/math.cc.i

CMakeFiles/raytracer.cc.dir/math.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raytracer.cc.dir/math.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/math.cc -o CMakeFiles/raytracer.cc.dir/math.cc.s

CMakeFiles/raytracer.cc.dir/geometry.cc.o: CMakeFiles/raytracer.cc.dir/flags.make
CMakeFiles/raytracer.cc.dir/geometry.cc.o: /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/geometry.cc
CMakeFiles/raytracer.cc.dir/geometry.cc.o: CMakeFiles/raytracer.cc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/raytracer.cc.dir/geometry.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytracer.cc.dir/geometry.cc.o -MF CMakeFiles/raytracer.cc.dir/geometry.cc.o.d -o CMakeFiles/raytracer.cc.dir/geometry.cc.o -c /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/geometry.cc

CMakeFiles/raytracer.cc.dir/geometry.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raytracer.cc.dir/geometry.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/geometry.cc > CMakeFiles/raytracer.cc.dir/geometry.cc.i

CMakeFiles/raytracer.cc.dir/geometry.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raytracer.cc.dir/geometry.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/geometry.cc -o CMakeFiles/raytracer.cc.dir/geometry.cc.s

# Object files for target raytracer.cc
raytracer_cc_OBJECTS = \
"CMakeFiles/raytracer.cc.dir/raytracer.cc.o" \
"CMakeFiles/raytracer.cc.dir/math.cc.o" \
"CMakeFiles/raytracer.cc.dir/geometry.cc.o"

# External object files for target raytracer.cc
raytracer_cc_EXTERNAL_OBJECTS =

raytracer.cc: CMakeFiles/raytracer.cc.dir/raytracer.cc.o
raytracer.cc: CMakeFiles/raytracer.cc.dir/math.cc.o
raytracer.cc: CMakeFiles/raytracer.cc.dir/geometry.cc.o
raytracer.cc: CMakeFiles/raytracer.cc.dir/build.make
raytracer.cc: CMakeFiles/raytracer.cc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable raytracer.cc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracer.cc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raytracer.cc.dir/build: raytracer.cc
.PHONY : CMakeFiles/raytracer.cc.dir/build

CMakeFiles/raytracer.cc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raytracer.cc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raytracer.cc.dir/clean

CMakeFiles/raytracer.cc.dir/depend:
	cd /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build /Users/noelrabenschlag/Desktop/Computergrafik/Raytracer/build/CMakeFiles/raytracer.cc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/raytracer.cc.dir/depend

