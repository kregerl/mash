# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/kregerl/CLionProjects/mash

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mash.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mash.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mash.dir/flags.make

CMakeFiles/mash.dir/src/main.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mash.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/main.cpp.o -c /mnt/c/Users/kregerl/CLionProjects/mash/src/main.cpp

CMakeFiles/mash.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/kregerl/CLionProjects/mash/src/main.cpp > CMakeFiles/mash.dir/src/main.cpp.i

CMakeFiles/mash.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/kregerl/CLionProjects/mash/src/main.cpp -o CMakeFiles/mash.dir/src/main.cpp.s

CMakeFiles/mash.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/mash.dir/src/main.cpp.o.requires

CMakeFiles/mash.dir/src/main.cpp.o.provides: CMakeFiles/mash.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mash.dir/build.make CMakeFiles/mash.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/mash.dir/src/main.cpp.o.provides

CMakeFiles/mash.dir/src/main.cpp.o.provides.build: CMakeFiles/mash.dir/src/main.cpp.o


CMakeFiles/mash.dir/src/Operations.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Operations.cpp.o: ../src/Operations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mash.dir/src/Operations.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Operations.cpp.o -c /mnt/c/Users/kregerl/CLionProjects/mash/src/Operations.cpp

CMakeFiles/mash.dir/src/Operations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Operations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/kregerl/CLionProjects/mash/src/Operations.cpp > CMakeFiles/mash.dir/src/Operations.cpp.i

CMakeFiles/mash.dir/src/Operations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Operations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/kregerl/CLionProjects/mash/src/Operations.cpp -o CMakeFiles/mash.dir/src/Operations.cpp.s

CMakeFiles/mash.dir/src/Operations.cpp.o.requires:

.PHONY : CMakeFiles/mash.dir/src/Operations.cpp.o.requires

CMakeFiles/mash.dir/src/Operations.cpp.o.provides: CMakeFiles/mash.dir/src/Operations.cpp.o.requires
	$(MAKE) -f CMakeFiles/mash.dir/build.make CMakeFiles/mash.dir/src/Operations.cpp.o.provides.build
.PHONY : CMakeFiles/mash.dir/src/Operations.cpp.o.provides

CMakeFiles/mash.dir/src/Operations.cpp.o.provides.build: CMakeFiles/mash.dir/src/Operations.cpp.o


CMakeFiles/mash.dir/src/Value.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Value.cpp.o: ../src/Value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mash.dir/src/Value.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Value.cpp.o -c /mnt/c/Users/kregerl/CLionProjects/mash/src/Value.cpp

CMakeFiles/mash.dir/src/Value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Value.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/kregerl/CLionProjects/mash/src/Value.cpp > CMakeFiles/mash.dir/src/Value.cpp.i

CMakeFiles/mash.dir/src/Value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Value.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/kregerl/CLionProjects/mash/src/Value.cpp -o CMakeFiles/mash.dir/src/Value.cpp.s

CMakeFiles/mash.dir/src/Value.cpp.o.requires:

.PHONY : CMakeFiles/mash.dir/src/Value.cpp.o.requires

CMakeFiles/mash.dir/src/Value.cpp.o.provides: CMakeFiles/mash.dir/src/Value.cpp.o.requires
	$(MAKE) -f CMakeFiles/mash.dir/build.make CMakeFiles/mash.dir/src/Value.cpp.o.provides.build
.PHONY : CMakeFiles/mash.dir/src/Value.cpp.o.provides

CMakeFiles/mash.dir/src/Value.cpp.o.provides.build: CMakeFiles/mash.dir/src/Value.cpp.o


# Object files for target mash
mash_OBJECTS = \
"CMakeFiles/mash.dir/src/main.cpp.o" \
"CMakeFiles/mash.dir/src/Operations.cpp.o" \
"CMakeFiles/mash.dir/src/Value.cpp.o"

# External object files for target mash
mash_EXTERNAL_OBJECTS =

mash: CMakeFiles/mash.dir/src/main.cpp.o
mash: CMakeFiles/mash.dir/src/Operations.cpp.o
mash: CMakeFiles/mash.dir/src/Value.cpp.o
mash: CMakeFiles/mash.dir/build.make
mash: CMakeFiles/mash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mash"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mash.dir/build: mash

.PHONY : CMakeFiles/mash.dir/build

CMakeFiles/mash.dir/requires: CMakeFiles/mash.dir/src/main.cpp.o.requires
CMakeFiles/mash.dir/requires: CMakeFiles/mash.dir/src/Operations.cpp.o.requires
CMakeFiles/mash.dir/requires: CMakeFiles/mash.dir/src/Value.cpp.o.requires

.PHONY : CMakeFiles/mash.dir/requires

CMakeFiles/mash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mash.dir/clean

CMakeFiles/mash.dir/depend:
	cd /mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/kregerl/CLionProjects/mash /mnt/c/Users/kregerl/CLionProjects/mash /mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug /mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug /mnt/c/Users/kregerl/CLionProjects/mash/cmake-build-debug/CMakeFiles/mash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mash.dir/depend

