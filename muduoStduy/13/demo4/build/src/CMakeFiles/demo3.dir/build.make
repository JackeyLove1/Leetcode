# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build

# Include any dependencies generated for this target.
include src/CMakeFiles/demo3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/demo3.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/demo3.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/demo3.dir/flags.make

src/CMakeFiles/demo3.dir/demo3.cpp.o: src/CMakeFiles/demo3.dir/flags.make
src/CMakeFiles/demo3.dir/demo3.cpp.o: ../src/demo3.cpp
src/CMakeFiles/demo3.dir/demo3.cpp.o: src/CMakeFiles/demo3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/demo3.dir/demo3.cpp.o"
	cd /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/demo3.dir/demo3.cpp.o -MF CMakeFiles/demo3.dir/demo3.cpp.o.d -o CMakeFiles/demo3.dir/demo3.cpp.o -c /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/src/demo3.cpp

src/CMakeFiles/demo3.dir/demo3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo3.dir/demo3.cpp.i"
	cd /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/src/demo3.cpp > CMakeFiles/demo3.dir/demo3.cpp.i

src/CMakeFiles/demo3.dir/demo3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo3.dir/demo3.cpp.s"
	cd /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/src/demo3.cpp -o CMakeFiles/demo3.dir/demo3.cpp.s

# Object files for target demo3
demo3_OBJECTS = \
"CMakeFiles/demo3.dir/demo3.cpp.o"

# External object files for target demo3
demo3_EXTERNAL_OBJECTS =

bin/demo3: src/CMakeFiles/demo3.dir/demo3.cpp.o
bin/demo3: src/CMakeFiles/demo3.dir/build.make
bin/demo3: lib/libmylib.a
bin/demo3: src/CMakeFiles/demo3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/demo3"
	cd /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/demo3.dir/build: bin/demo3
.PHONY : src/CMakeFiles/demo3.dir/build

src/CMakeFiles/demo3.dir/clean:
	cd /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src && $(CMAKE_COMMAND) -P CMakeFiles/demo3.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/demo3.dir/clean

src/CMakeFiles/demo3.dir/depend:
	cd /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4 /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/src /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src /Users/arexiusvan/Desktop/Leetcode/muduoStduy/13/demo4/build/src/CMakeFiles/demo3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/demo3.dir/depend

