# XML Processing Library Module
cmake_minimum_required(VERSION 3.10)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define library source files
set(LIB_SOURCES
    xml_lib.cpp
    DrawGraph.cpp
    xmltojsonconverter.cpp
)

set(LIB_HEADERS
    xml_lib.h
    DrawGraph.h
    xmltojsonconverter.h
)

# Create static library
add_library(xml_processing_lib STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set include directory for the library
target_include_directories(xml_processing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set library output name
set_target_properties(xml_processing_lib PROPERTIES OUTPUT_NAME "xml_processing")
