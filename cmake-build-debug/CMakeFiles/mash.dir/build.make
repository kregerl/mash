# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/loucas/AppImage/clion-2021.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/loucas/AppImage/clion-2021.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/loucas/CLionProjects/mash

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/loucas/CLionProjects/mash/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mash.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/mash.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mash.dir/flags.make

CMakeFiles/mash.dir/src/main.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mash.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/main.cpp.o -c /home/loucas/CLionProjects/mash/src/main.cpp

CMakeFiles/mash.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/main.cpp > CMakeFiles/mash.dir/src/main.cpp.i

CMakeFiles/mash.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/main.cpp -o CMakeFiles/mash.dir/src/main.cpp.s

CMakeFiles/mash.dir/src/Operations.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Operations.cpp.o: ../src/Operations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mash.dir/src/Operations.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Operations.cpp.o -c /home/loucas/CLionProjects/mash/src/Operations.cpp

CMakeFiles/mash.dir/src/Operations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Operations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Operations.cpp > CMakeFiles/mash.dir/src/Operations.cpp.i

CMakeFiles/mash.dir/src/Operations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Operations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Operations.cpp -o CMakeFiles/mash.dir/src/Operations.cpp.s

CMakeFiles/mash.dir/src/Value.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Value.cpp.o: ../src/Value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mash.dir/src/Value.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Value.cpp.o -c /home/loucas/CLionProjects/mash/src/Value.cpp

CMakeFiles/mash.dir/src/Value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Value.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Value.cpp > CMakeFiles/mash.dir/src/Value.cpp.i

CMakeFiles/mash.dir/src/Value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Value.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Value.cpp -o CMakeFiles/mash.dir/src/Value.cpp.s

CMakeFiles/mash.dir/src/Collection1D.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Collection1D.cpp.o: ../src/Collection1D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mash.dir/src/Collection1D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Collection1D.cpp.o -c /home/loucas/CLionProjects/mash/src/Collection1D.cpp

CMakeFiles/mash.dir/src/Collection1D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Collection1D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Collection1D.cpp > CMakeFiles/mash.dir/src/Collection1D.cpp.i

CMakeFiles/mash.dir/src/Collection1D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Collection1D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Collection1D.cpp -o CMakeFiles/mash.dir/src/Collection1D.cpp.s

CMakeFiles/mash.dir/src/Vector.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Vector.cpp.o: ../src/Vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mash.dir/src/Vector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Vector.cpp.o -c /home/loucas/CLionProjects/mash/src/Vector.cpp

CMakeFiles/mash.dir/src/Vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Vector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Vector.cpp > CMakeFiles/mash.dir/src/Vector.cpp.i

CMakeFiles/mash.dir/src/Vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Vector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Vector.cpp -o CMakeFiles/mash.dir/src/Vector.cpp.s

CMakeFiles/mash.dir/src/Set.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Set.cpp.o: ../src/Set.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mash.dir/src/Set.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Set.cpp.o -c /home/loucas/CLionProjects/mash/src/Set.cpp

CMakeFiles/mash.dir/src/Set.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Set.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Set.cpp > CMakeFiles/mash.dir/src/Set.cpp.i

CMakeFiles/mash.dir/src/Set.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Set.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Set.cpp -o CMakeFiles/mash.dir/src/Set.cpp.s

CMakeFiles/mash.dir/src/Number.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Number.cpp.o: ../src/Number.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mash.dir/src/Number.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Number.cpp.o -c /home/loucas/CLionProjects/mash/src/Number.cpp

CMakeFiles/mash.dir/src/Number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Number.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Number.cpp > CMakeFiles/mash.dir/src/Number.cpp.i

CMakeFiles/mash.dir/src/Number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Number.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Number.cpp -o CMakeFiles/mash.dir/src/Number.cpp.s

CMakeFiles/mash.dir/src/Lexer.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Lexer.cpp.o: ../src/Lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mash.dir/src/Lexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Lexer.cpp.o -c /home/loucas/CLionProjects/mash/src/Lexer.cpp

CMakeFiles/mash.dir/src/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Lexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Lexer.cpp > CMakeFiles/mash.dir/src/Lexer.cpp.i

CMakeFiles/mash.dir/src/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Lexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Lexer.cpp -o CMakeFiles/mash.dir/src/Lexer.cpp.s

CMakeFiles/mash.dir/src/Parser.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Parser.cpp.o: ../src/Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/mash.dir/src/Parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Parser.cpp.o -c /home/loucas/CLionProjects/mash/src/Parser.cpp

CMakeFiles/mash.dir/src/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Parser.cpp > CMakeFiles/mash.dir/src/Parser.cpp.i

CMakeFiles/mash.dir/src/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Parser.cpp -o CMakeFiles/mash.dir/src/Parser.cpp.s

CMakeFiles/mash.dir/src/Interpreter.cpp.o: CMakeFiles/mash.dir/flags.make
CMakeFiles/mash.dir/src/Interpreter.cpp.o: ../src/Interpreter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/mash.dir/src/Interpreter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mash.dir/src/Interpreter.cpp.o -c /home/loucas/CLionProjects/mash/src/Interpreter.cpp

CMakeFiles/mash.dir/src/Interpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mash.dir/src/Interpreter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loucas/CLionProjects/mash/src/Interpreter.cpp > CMakeFiles/mash.dir/src/Interpreter.cpp.i

CMakeFiles/mash.dir/src/Interpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mash.dir/src/Interpreter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loucas/CLionProjects/mash/src/Interpreter.cpp -o CMakeFiles/mash.dir/src/Interpreter.cpp.s

# Object files for target mash
mash_OBJECTS = \
"CMakeFiles/mash.dir/src/main.cpp.o" \
"CMakeFiles/mash.dir/src/Operations.cpp.o" \
"CMakeFiles/mash.dir/src/Value.cpp.o" \
"CMakeFiles/mash.dir/src/Collection1D.cpp.o" \
"CMakeFiles/mash.dir/src/Vector.cpp.o" \
"CMakeFiles/mash.dir/src/Set.cpp.o" \
"CMakeFiles/mash.dir/src/Number.cpp.o" \
"CMakeFiles/mash.dir/src/Lexer.cpp.o" \
"CMakeFiles/mash.dir/src/Parser.cpp.o" \
"CMakeFiles/mash.dir/src/Interpreter.cpp.o"

# External object files for target mash
mash_EXTERNAL_OBJECTS =

mash: CMakeFiles/mash.dir/src/main.cpp.o
mash: CMakeFiles/mash.dir/src/Operations.cpp.o
mash: CMakeFiles/mash.dir/src/Value.cpp.o
mash: CMakeFiles/mash.dir/src/Collection1D.cpp.o
mash: CMakeFiles/mash.dir/src/Vector.cpp.o
mash: CMakeFiles/mash.dir/src/Set.cpp.o
mash: CMakeFiles/mash.dir/src/Number.cpp.o
mash: CMakeFiles/mash.dir/src/Lexer.cpp.o
mash: CMakeFiles/mash.dir/src/Parser.cpp.o
mash: CMakeFiles/mash.dir/src/Interpreter.cpp.o
mash: CMakeFiles/mash.dir/build.make
mash: CMakeFiles/mash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable mash"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mash.dir/build: mash
.PHONY : CMakeFiles/mash.dir/build

CMakeFiles/mash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mash.dir/clean

CMakeFiles/mash.dir/depend:
	cd /home/loucas/CLionProjects/mash/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/loucas/CLionProjects/mash /home/loucas/CLionProjects/mash /home/loucas/CLionProjects/mash/cmake-build-debug /home/loucas/CLionProjects/mash/cmake-build-debug /home/loucas/CLionProjects/mash/cmake-build-debug/CMakeFiles/mash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mash.dir/depend

