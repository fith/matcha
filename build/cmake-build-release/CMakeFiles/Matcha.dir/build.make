# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kevin/Workspace/c/matcha

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kevin/Workspace/c/matcha/build/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/Matcha.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Matcha.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Matcha.dir/flags.make

CMakeFiles/Matcha.dir/src/engine/draw.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/engine/draw.c.o: ../../src/engine/draw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Matcha.dir/src/engine/draw.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/engine/draw.c.o   -c /Users/kevin/Workspace/c/matcha/src/engine/draw.c

CMakeFiles/Matcha.dir/src/engine/draw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/engine/draw.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/engine/draw.c > CMakeFiles/Matcha.dir/src/engine/draw.c.i

CMakeFiles/Matcha.dir/src/engine/draw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/engine/draw.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/engine/draw.c -o CMakeFiles/Matcha.dir/src/engine/draw.c.s

CMakeFiles/Matcha.dir/src/engine/init.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/engine/init.c.o: ../../src/engine/init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Matcha.dir/src/engine/init.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/engine/init.c.o   -c /Users/kevin/Workspace/c/matcha/src/engine/init.c

CMakeFiles/Matcha.dir/src/engine/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/engine/init.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/engine/init.c > CMakeFiles/Matcha.dir/src/engine/init.c.i

CMakeFiles/Matcha.dir/src/engine/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/engine/init.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/engine/init.c -o CMakeFiles/Matcha.dir/src/engine/init.c.s

CMakeFiles/Matcha.dir/src/engine/input.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/engine/input.c.o: ../../src/engine/input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Matcha.dir/src/engine/input.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/engine/input.c.o   -c /Users/kevin/Workspace/c/matcha/src/engine/input.c

CMakeFiles/Matcha.dir/src/engine/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/engine/input.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/engine/input.c > CMakeFiles/Matcha.dir/src/engine/input.c.i

CMakeFiles/Matcha.dir/src/engine/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/engine/input.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/engine/input.c -o CMakeFiles/Matcha.dir/src/engine/input.c.s

CMakeFiles/Matcha.dir/src/app/level1.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/app/level1.c.o: ../../src/app/level1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Matcha.dir/src/app/level1.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/app/level1.c.o   -c /Users/kevin/Workspace/c/matcha/src/app/level1.c

CMakeFiles/Matcha.dir/src/app/level1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/app/level1.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/app/level1.c > CMakeFiles/Matcha.dir/src/app/level1.c.i

CMakeFiles/Matcha.dir/src/app/level1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/app/level1.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/app/level1.c -o CMakeFiles/Matcha.dir/src/app/level1.c.s

CMakeFiles/Matcha.dir/src/main.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/main.c.o: ../../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Matcha.dir/src/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/main.c.o   -c /Users/kevin/Workspace/c/matcha/src/main.c

CMakeFiles/Matcha.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/main.c > CMakeFiles/Matcha.dir/src/main.c.i

CMakeFiles/Matcha.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/main.c -o CMakeFiles/Matcha.dir/src/main.c.s

CMakeFiles/Matcha.dir/src/data/colors.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/data/colors.c.o: ../../src/data/colors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Matcha.dir/src/data/colors.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/data/colors.c.o   -c /Users/kevin/Workspace/c/matcha/src/data/colors.c

CMakeFiles/Matcha.dir/src/data/colors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/data/colors.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/data/colors.c > CMakeFiles/Matcha.dir/src/data/colors.c.i

CMakeFiles/Matcha.dir/src/data/colors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/data/colors.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/data/colors.c -o CMakeFiles/Matcha.dir/src/data/colors.c.s

CMakeFiles/Matcha.dir/src/data/levels.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/data/levels.c.o: ../../src/data/levels.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Matcha.dir/src/data/levels.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/data/levels.c.o   -c /Users/kevin/Workspace/c/matcha/src/data/levels.c

CMakeFiles/Matcha.dir/src/data/levels.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/data/levels.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/data/levels.c > CMakeFiles/Matcha.dir/src/data/levels.c.i

CMakeFiles/Matcha.dir/src/data/levels.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/data/levels.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/data/levels.c -o CMakeFiles/Matcha.dir/src/data/levels.c.s

CMakeFiles/Matcha.dir/src/app/menu.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/app/menu.c.o: ../../src/app/menu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Matcha.dir/src/app/menu.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/app/menu.c.o   -c /Users/kevin/Workspace/c/matcha/src/app/menu.c

CMakeFiles/Matcha.dir/src/app/menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/app/menu.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/app/menu.c > CMakeFiles/Matcha.dir/src/app/menu.c.i

CMakeFiles/Matcha.dir/src/app/menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/app/menu.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/app/menu.c -o CMakeFiles/Matcha.dir/src/app/menu.c.s

CMakeFiles/Matcha.dir/src/app/options.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/app/options.c.o: ../../src/app/options.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/Matcha.dir/src/app/options.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/app/options.c.o   -c /Users/kevin/Workspace/c/matcha/src/app/options.c

CMakeFiles/Matcha.dir/src/app/options.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/app/options.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/app/options.c > CMakeFiles/Matcha.dir/src/app/options.c.i

CMakeFiles/Matcha.dir/src/app/options.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/app/options.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/app/options.c -o CMakeFiles/Matcha.dir/src/app/options.c.s

CMakeFiles/Matcha.dir/src/engine/sound.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/engine/sound.c.o: ../../src/engine/sound.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/Matcha.dir/src/engine/sound.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/engine/sound.c.o   -c /Users/kevin/Workspace/c/matcha/src/engine/sound.c

CMakeFiles/Matcha.dir/src/engine/sound.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/engine/sound.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/engine/sound.c > CMakeFiles/Matcha.dir/src/engine/sound.c.i

CMakeFiles/Matcha.dir/src/engine/sound.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/engine/sound.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/engine/sound.c -o CMakeFiles/Matcha.dir/src/engine/sound.c.s

CMakeFiles/Matcha.dir/src/engine/text.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/engine/text.c.o: ../../src/engine/text.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/Matcha.dir/src/engine/text.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/engine/text.c.o   -c /Users/kevin/Workspace/c/matcha/src/engine/text.c

CMakeFiles/Matcha.dir/src/engine/text.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/engine/text.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/engine/text.c > CMakeFiles/Matcha.dir/src/engine/text.c.i

CMakeFiles/Matcha.dir/src/engine/text.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/engine/text.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/engine/text.c -o CMakeFiles/Matcha.dir/src/engine/text.c.s

CMakeFiles/Matcha.dir/src/engine/util.c.o: CMakeFiles/Matcha.dir/flags.make
CMakeFiles/Matcha.dir/src/engine/util.c.o: ../../src/engine/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/Matcha.dir/src/engine/util.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Matcha.dir/src/engine/util.c.o   -c /Users/kevin/Workspace/c/matcha/src/engine/util.c

CMakeFiles/Matcha.dir/src/engine/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matcha.dir/src/engine/util.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/kevin/Workspace/c/matcha/src/engine/util.c > CMakeFiles/Matcha.dir/src/engine/util.c.i

CMakeFiles/Matcha.dir/src/engine/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matcha.dir/src/engine/util.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/kevin/Workspace/c/matcha/src/engine/util.c -o CMakeFiles/Matcha.dir/src/engine/util.c.s

# Object files for target Matcha
Matcha_OBJECTS = \
"CMakeFiles/Matcha.dir/src/engine/draw.c.o" \
"CMakeFiles/Matcha.dir/src/engine/init.c.o" \
"CMakeFiles/Matcha.dir/src/engine/input.c.o" \
"CMakeFiles/Matcha.dir/src/app/level1.c.o" \
"CMakeFiles/Matcha.dir/src/main.c.o" \
"CMakeFiles/Matcha.dir/src/data/colors.c.o" \
"CMakeFiles/Matcha.dir/src/data/levels.c.o" \
"CMakeFiles/Matcha.dir/src/app/menu.c.o" \
"CMakeFiles/Matcha.dir/src/app/options.c.o" \
"CMakeFiles/Matcha.dir/src/engine/sound.c.o" \
"CMakeFiles/Matcha.dir/src/engine/text.c.o" \
"CMakeFiles/Matcha.dir/src/engine/util.c.o"

# External object files for target Matcha
Matcha_EXTERNAL_OBJECTS =

bin/Matcha: CMakeFiles/Matcha.dir/src/engine/draw.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/engine/init.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/engine/input.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/app/level1.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/main.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/data/colors.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/data/levels.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/app/menu.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/app/options.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/engine/sound.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/engine/text.c.o
bin/Matcha: CMakeFiles/Matcha.dir/src/engine/util.c.o
bin/Matcha: CMakeFiles/Matcha.dir/build.make
bin/Matcha: CMakeFiles/Matcha.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C executable bin/Matcha"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Matcha.dir/link.txt --verbose=$(VERBOSE)
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy_directory /Users/kevin/Workspace/c/matcha/resources /Users/kevin/Workspace/c/matcha/build/cmake-build-release/bin/resources

# Rule to build all files generated by this target.
CMakeFiles/Matcha.dir/build: bin/Matcha

.PHONY : CMakeFiles/Matcha.dir/build

CMakeFiles/Matcha.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Matcha.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Matcha.dir/clean

CMakeFiles/Matcha.dir/depend:
	cd /Users/kevin/Workspace/c/matcha/build/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kevin/Workspace/c/matcha /Users/kevin/Workspace/c/matcha /Users/kevin/Workspace/c/matcha/build/cmake-build-release /Users/kevin/Workspace/c/matcha/build/cmake-build-release /Users/kevin/Workspace/c/matcha/build/cmake-build-release/CMakeFiles/Matcha.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Matcha.dir/depend

