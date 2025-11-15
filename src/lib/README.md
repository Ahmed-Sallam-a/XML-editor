# XML Processing Library Module

This directory contains the core XML processing library for the XML Editor project.

## Components

### xml_lib.h / xml_lib.cpp
Core XML processing functionality including:
- XML consistency checking and error fixing
- XML formatting (prettify/minify)
- User management and follower analysis
- Post searching
- XML compression/decompression

### DrawGraph.h / DrawGraph.cpp
Graph visualization functionality for XML data:
- Parse XML user data and build graph structures
- Generate DOT files for visualization
- Convert to PNG format

### xmltojsonconverter.h / xmltojsonconverter.cpp
XML to JSON conversion utilities:
- Parse XML into tree structure
- Convert XML nodes to JSON format
- Handle attributes and nested elements

## Building

This module is built as a static library (`libxml_processing.a`) that can be linked with applications.

### Using CMake:

```bash
# From the project root
mkdir build && cd build
cmake ..
make
```

The library will be built in `build/src/lib/libxml_processing.a`

## Usage

Include the library headers in your application:

```cpp
#include "xml_lib.h"
#include "DrawGraph.h"
#include "xmltojsonconverter.h"
```

Link with the library when building:

```bash
g++ -o your_app your_app.cpp -L/path/to/lib -lxml_processing
```

Or use CMake:

```cmake
target_link_libraries(your_app xml_processing_lib)
```

## API Reference

See the individual header files for detailed API documentation:
- `xml_lib.h` - Core XML processing functions
- `DrawGraph.h` - Graph visualization classes and functions
- `xmltojsonconverter.h` - XML to JSON conversion
