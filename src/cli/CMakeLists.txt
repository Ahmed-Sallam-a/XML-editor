# XML Editor CLI Application Module
cmake_minimum_required(VERSION 3.10)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define CLI executable
add_executable(xml_editor main.cpp)

# Link with the XML processing library
target_link_libraries(xml_editor xml_processing_lib)

# Include library headers
target_include_directories(xml_editor PRIVATE ${CMAKE_SOURCE_DIR}/lib)
