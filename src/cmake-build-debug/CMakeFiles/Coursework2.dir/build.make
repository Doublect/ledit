# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Coursework2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Coursework2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Coursework2.dir/flags.make

CMakeFiles/Coursework2.dir/Coursework2.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/Coursework2.c.o: ../Coursework2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Coursework2.dir/Coursework2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/Coursework2.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Coursework2.c

CMakeFiles/Coursework2.dir/Coursework2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/Coursework2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Coursework2.c > CMakeFiles/Coursework2.dir/Coursework2.c.i

CMakeFiles/Coursework2.dir/Coursework2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/Coursework2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Coursework2.c -o CMakeFiles/Coursework2.dir/Coursework2.c.s

CMakeFiles/Coursework2.dir/Renderer.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/Renderer.c.o: ../Renderer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Coursework2.dir/Renderer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/Renderer.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Renderer.c

CMakeFiles/Coursework2.dir/Renderer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/Renderer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Renderer.c > CMakeFiles/Coursework2.dir/Renderer.c.i

CMakeFiles/Coursework2.dir/Renderer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/Renderer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Renderer.c -o CMakeFiles/Coursework2.dir/Renderer.c.s

CMakeFiles/Coursework2.dir/FileIO.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/FileIO.c.o: ../FileIO.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Coursework2.dir/FileIO.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/FileIO.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/FileIO.c

CMakeFiles/Coursework2.dir/FileIO.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/FileIO.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/FileIO.c > CMakeFiles/Coursework2.dir/FileIO.c.i

CMakeFiles/Coursework2.dir/FileIO.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/FileIO.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/FileIO.c -o CMakeFiles/Coursework2.dir/FileIO.c.s

CMakeFiles/Coursework2.dir/Terminal.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/Terminal.c.o: ../Terminal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Coursework2.dir/Terminal.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/Terminal.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Terminal.c

CMakeFiles/Coursework2.dir/Terminal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/Terminal.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Terminal.c > CMakeFiles/Coursework2.dir/Terminal.c.i

CMakeFiles/Coursework2.dir/Terminal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/Terminal.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Terminal.c -o CMakeFiles/Coursework2.dir/Terminal.c.s

CMakeFiles/Coursework2.dir/TextHandler.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/TextHandler.c.o: ../TextHandler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Coursework2.dir/TextHandler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/TextHandler.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/TextHandler.c

CMakeFiles/Coursework2.dir/TextHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/TextHandler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/TextHandler.c > CMakeFiles/Coursework2.dir/TextHandler.c.i

CMakeFiles/Coursework2.dir/TextHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/TextHandler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/TextHandler.c -o CMakeFiles/Coursework2.dir/TextHandler.c.s

CMakeFiles/Coursework2.dir/Library.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/Library.c.o: ../Library.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Coursework2.dir/Library.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/Library.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Library.c

CMakeFiles/Coursework2.dir/Library.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/Library.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Library.c > CMakeFiles/Coursework2.dir/Library.c.i

CMakeFiles/Coursework2.dir/Library.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/Library.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Library.c -o CMakeFiles/Coursework2.dir/Library.c.s

CMakeFiles/Coursework2.dir/Commands.c.o: CMakeFiles/Coursework2.dir/flags.make
CMakeFiles/Coursework2.dir/Commands.c.o: ../Commands.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Coursework2.dir/Commands.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Coursework2.dir/Commands.c.o -c /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Commands.c

CMakeFiles/Coursework2.dir/Commands.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework2.dir/Commands.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Commands.c > CMakeFiles/Coursework2.dir/Commands.c.i

CMakeFiles/Coursework2.dir/Commands.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework2.dir/Commands.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/Commands.c -o CMakeFiles/Coursework2.dir/Commands.c.s

# Object files for target Coursework2
Coursework2_OBJECTS = \
"CMakeFiles/Coursework2.dir/Coursework2.c.o" \
"CMakeFiles/Coursework2.dir/Renderer.c.o" \
"CMakeFiles/Coursework2.dir/FileIO.c.o" \
"CMakeFiles/Coursework2.dir/Terminal.c.o" \
"CMakeFiles/Coursework2.dir/TextHandler.c.o" \
"CMakeFiles/Coursework2.dir/Library.c.o" \
"CMakeFiles/Coursework2.dir/Commands.c.o"

# External object files for target Coursework2
Coursework2_EXTERNAL_OBJECTS =

Coursework2: CMakeFiles/Coursework2.dir/Coursework2.c.o
Coursework2: CMakeFiles/Coursework2.dir/Renderer.c.o
Coursework2: CMakeFiles/Coursework2.dir/FileIO.c.o
Coursework2: CMakeFiles/Coursework2.dir/Terminal.c.o
Coursework2: CMakeFiles/Coursework2.dir/TextHandler.c.o
Coursework2: CMakeFiles/Coursework2.dir/Library.c.o
Coursework2: CMakeFiles/Coursework2.dir/Commands.c.o
Coursework2: CMakeFiles/Coursework2.dir/build.make
Coursework2: CMakeFiles/Coursework2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable Coursework2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Coursework2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Coursework2.dir/build: Coursework2

.PHONY : CMakeFiles/Coursework2.dir/build

CMakeFiles/Coursework2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Coursework2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Coursework2.dir/clean

CMakeFiles/Coursework2.dir/depend:
	cd /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug /mnt/nvme0n1p4/Personal/University/cs132/Coursework2/src/cmake-build-debug/CMakeFiles/Coursework2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Coursework2.dir/depend

