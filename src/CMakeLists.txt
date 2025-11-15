# This CMakeLists.txt is deprecated. Use the top-level CMakeLists.txt instead.
# For backward compatibility, you can still build from here:
cmake_minimum_required(VERSION 3.10)
project(src)

set(CMAKE_CXX_STANDARD 14)

# Build the library and CLI from subdirectories
add_subdirectory(lib)
add_subdirectory(cli)
