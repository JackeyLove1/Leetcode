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
CMAKE_COMMAND = /Users/arexiusvan/anaconda3/lib/python3.8/site-packages/cmake/data/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Users/arexiusvan/anaconda3/lib/python3.8/site-packages/cmake/data/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/arexiusvan/CLionProjects/202204/Demo9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/arexiusvan/CLionProjects/202204/Demo9/build

# Include any dependencies generated for this target.
include sublib1/CMakeFiles/hello.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sublib1/CMakeFiles/hello.dir/compiler_depend.make

# Include the progress variables for this target.
include sublib1/CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include sublib1/CMakeFiles/hello.dir/flags.make

sublib1/CMakeFiles/hello.dir/src/hello.cpp.o: sublib1/CMakeFiles/hello.dir/flags.make
sublib1/CMakeFiles/hello.dir/src/hello.cpp.o: ../sublib1/src/hello.cpp
sublib1/CMakeFiles/hello.dir/src/hello.cpp.o: sublib1/CMakeFiles/hello.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/arexiusvan/CLionProjects/202204/Demo9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sublib1/CMakeFiles/hello.dir/src/hello.cpp.o"
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sublib1/CMakeFiles/hello.dir/src/hello.cpp.o -MF CMakeFiles/hello.dir/src/hello.cpp.o.d -o CMakeFiles/hello.dir/src/hello.cpp.o -c /Users/arexiusvan/CLionProjects/202204/Demo9/sublib1/src/hello.cpp

sublib1/CMakeFiles/hello.dir/src/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hello.dir/src/hello.cpp.i"
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arexiusvan/CLionProjects/202204/Demo9/sublib1/src/hello.cpp > CMakeFiles/hello.dir/src/hello.cpp.i

sublib1/CMakeFiles/hello.dir/src/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hello.dir/src/hello.cpp.s"
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arexiusvan/CLionProjects/202204/Demo9/sublib1/src/hello.cpp -o CMakeFiles/hello.dir/src/hello.cpp.s

# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/src/hello.cpp.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

sublib1/libhello.a: sublib1/CMakeFiles/hello.dir/src/hello.cpp.o
sublib1/libhello.a: sublib1/CMakeFiles/hello.dir/build.make
sublib1/libhello.a: sublib1/CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/arexiusvan/CLionProjects/202204/Demo9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libhello.a"
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean_target.cmake
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sublib1/CMakeFiles/hello.dir/build: sublib1/libhello.a
.PHONY : sublib1/CMakeFiles/hello.dir/build

sublib1/CMakeFiles/hello.dir/clean:
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : sublib1/CMakeFiles/hello.dir/clean

sublib1/CMakeFiles/hello.dir/depend:
	cd /Users/arexiusvan/CLionProjects/202204/Demo9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/arexiusvan/CLionProjects/202204/Demo9 /Users/arexiusvan/CLionProjects/202204/Demo9/sublib1 /Users/arexiusvan/CLionProjects/202204/Demo9/build /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1 /Users/arexiusvan/CLionProjects/202204/Demo9/build/sublib1/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sublib1/CMakeFiles/hello.dir/depend

