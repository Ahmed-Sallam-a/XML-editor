# XML Editor CLI Application

This directory contains the command-line interface application for the XML Editor project.

## Overview

The CLI application provides a command-line interface to the XML processing library, allowing users to perform various XML operations from the terminal.

## Building

### Using CMake:

```bash
# From the project root
mkdir build && cd build
cmake ..
make
```

The executable will be built in `build/src/cli/xml_editor`

## Usage

```bash
xml_editor <command> [options]
```

### Available Commands

1. **verify** - Check XML consistency
   ```bash
   xml_editor verify -i input.xml [-f] [-o output.xml]
   ```

2. **format** - Prettify XML
   ```bash
   xml_editor format -i input.xml -o output.xml
   ```

3. **mini** - Minify XML
   ```bash
   xml_editor mini -i input.xml -o output.xml
   ```

4. **json** - Convert XML to JSON
   ```bash
   xml_editor json -i input.xml -o output.json
   ```

5. **compress** - Compress XML
   ```bash
   xml_editor compress -i input.xml -o output.comp
   ```

6. **decompress** - Decompress XML
   ```bash
   xml_editor decompress -i input.comp -o output.xml
   ```

7. **draw** - Generate graph visualization
   ```bash
   xml_editor draw -i input.xml -o output.jpg
   ```

8. **most_active** - Find most active user
   ```bash
   xml_editor most_active -i input.xml
   ```

9. **most_influencer** - Find most influential user
   ```bash
   xml_editor most_influencer -i input.xml
   ```

10. **mutual** - Find mutual followers
    ```bash
    xml_editor mutual -i input.xml -ids 1,2,3
    ```

11. **suggest** - Suggest users to follow
    ```bash
    xml_editor suggest -i input.xml -id 1
    ```

12. **search** - Search posts
    ```bash
    xml_editor search -w word -i input.xml
    xml_editor search -t topic -i input.xml
    ```

## Dependencies

This application depends on the XML processing library (`xml_processing_lib`).
