# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LMS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LMS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LMS.dir/flags.make

CMakeFiles/LMS.dir/main.cpp.o: CMakeFiles/LMS.dir/flags.make
CMakeFiles/LMS.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LMS.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LMS.dir/main.cpp.o -c /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/main.cpp

CMakeFiles/LMS.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LMS.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/main.cpp > CMakeFiles/LMS.dir/main.cpp.i

CMakeFiles/LMS.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LMS.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/main.cpp -o CMakeFiles/LMS.dir/main.cpp.s

# Object files for target LMS
LMS_OBJECTS = \
"CMakeFiles/LMS.dir/main.cpp.o"

# External object files for target LMS
LMS_EXTERNAL_OBJECTS =

LMS: CMakeFiles/LMS.dir/main.cpp.o
LMS: CMakeFiles/LMS.dir/build.make
LMS: CMakeFiles/LMS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LMS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LMS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LMS.dir/build: LMS

.PHONY : CMakeFiles/LMS.dir/build

CMakeFiles/LMS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LMS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LMS.dir/clean

CMakeFiles/LMS.dir/depend:
	cd /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug /Users/wangzilong/Desktop/Study/Assignment/综合训练/LMS/cmake-build-debug/CMakeFiles/LMS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LMS.dir/depend
