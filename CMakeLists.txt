# XML Editor Project - Top Level Build Configuration
cmake_minimum_required(VERSION 3.10)
project(XML_Editor VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for modular build
add_subdirectory(src/lib)
add_subdirectory(src/cli)

# Optional: Add install targets
install(TARGETS xml_editor DESTINATION bin)
install(TARGETS xml_processing_lib DESTINATION lib)
install(FILES 
    src/lib/xml_lib.h 
    src/lib/DrawGraph.h 
    src/lib/xmltojsonconverter.h 
    DESTINATION include/xml_processing)
