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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ymirth/study/cpp_code/linux_learning/Rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ymirth/study/cpp_code/linux_learning/Rpc/build

# Include any dependencies generated for this target.
include example/CMakeFiles/myrpcclient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/myrpcclient.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/myrpcclient.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/myrpcclient.dir/flags.make

example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o: example/CMakeFiles/myrpcclient.dir/flags.make
example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o: ../example/client/rpcclient.cpp
example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o: example/CMakeFiles/myrpcclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymirth/study/cpp_code/linux_learning/Rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && /opt/rh/devtoolset-9/root/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o -MF CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o.d -o CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o -c /home/ymirth/study/cpp_code/linux_learning/Rpc/example/client/rpcclient.cpp

example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.i"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && /opt/rh/devtoolset-9/root/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ymirth/study/cpp_code/linux_learning/Rpc/example/client/rpcclient.cpp > CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.i

example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.s"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && /opt/rh/devtoolset-9/root/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ymirth/study/cpp_code/linux_learning/Rpc/example/client/rpcclient.cpp -o CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.s

example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o: example/CMakeFiles/myrpcclient.dir/flags.make
example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o: ../example/protos/example.service.pb.cc
example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o: example/CMakeFiles/myrpcclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymirth/study/cpp_code/linux_learning/Rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && /opt/rh/devtoolset-9/root/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o -MF CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o.d -o CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o -c /home/ymirth/study/cpp_code/linux_learning/Rpc/example/protos/example.service.pb.cc

example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.i"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && /opt/rh/devtoolset-9/root/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ymirth/study/cpp_code/linux_learning/Rpc/example/protos/example.service.pb.cc > CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.i

example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.s"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && /opt/rh/devtoolset-9/root/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ymirth/study/cpp_code/linux_learning/Rpc/example/protos/example.service.pb.cc -o CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.s

# Object files for target myrpcclient
myrpcclient_OBJECTS = \
"CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o" \
"CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o"

# External object files for target myrpcclient
myrpcclient_EXTERNAL_OBJECTS =

../bin/myrpcclient: example/CMakeFiles/myrpcclient.dir/client/rpcclient.cpp.o
../bin/myrpcclient: example/CMakeFiles/myrpcclient.dir/protos/example.service.pb.cc.o
../bin/myrpcclient: example/CMakeFiles/myrpcclient.dir/build.make
../bin/myrpcclient: ../lib/libmyrpc.a
../bin/myrpcclient: example/CMakeFiles/myrpcclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ymirth/study/cpp_code/linux_learning/Rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/myrpcclient"
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myrpcclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/myrpcclient.dir/build: ../bin/myrpcclient
.PHONY : example/CMakeFiles/myrpcclient.dir/build

example/CMakeFiles/myrpcclient.dir/clean:
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example && $(CMAKE_COMMAND) -P CMakeFiles/myrpcclient.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/myrpcclient.dir/clean

example/CMakeFiles/myrpcclient.dir/depend:
	cd /home/ymirth/study/cpp_code/linux_learning/Rpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ymirth/study/cpp_code/linux_learning/Rpc /home/ymirth/study/cpp_code/linux_learning/Rpc/example /home/ymirth/study/cpp_code/linux_learning/Rpc/build /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example /home/ymirth/study/cpp_code/linux_learning/Rpc/build/example/CMakeFiles/myrpcclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/myrpcclient.dir/depend

