# XML Processing Library

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Command Line Interface](#command-line-interface)
  - [Graphical User Interface](#graphical-user-interface)
- [Data Structures](#data-structures)
- [Functions](#functions)
  - [Helper Functions](#helper-functions)
  - [XML Consistency](#xml-consistency)
  - [User Management](#user-management)
  - [Post Search](#post-search)
  - [XML Formatting](#xml-formatting)
  - [Compression](#compression)
- [Complexity](#complexity)
- [References](#references)

## Introduction

This project is an XML processing library designed to handle various XML-related tasks such as consistency checking, formatting, and user-following management. It ensures XML data integrity, improves readability, and manages user relationships.

## Features

- XML consistency checking and error fixing
- User management and mutual follower detection
- Post search by word or topic
- XML prettifying and minifying
- XML compression and decompression
- XML to JSON conversion
- Graphical representation of XML data

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/your-repo/xml-processing-library.git
    ```

2. Navigate to the project directory:

    ```sh
    cd xml-processing-library
    ```

3. Compile the project:

    ```sh
    g++ -o xml_processor src/xml_lib.cpp src/main.cpp
    ```

## Usage

### Command Line Interface

1. **Check XML Consistency**:

    ```sh
    ./xml_processor verify -i input.xml [-f] [-o output.xml]
    ```

    - `-f`: Fix errors if found
    - `-o`: Specify output file for corrected XML

2. **Prettify XML**:

    ```sh
    ./xml_processor format -i input.xml -o output.xml
    ```

3. **Minify XML**:

    ```sh
    ./xml_processor mini -i input.xml -o output.xml
    ```

4. **Compress XML**:

    ```sh
    ./xml_processor compress -i input.xml -o output.comp
    ```

5. **Decompress XML**:

    ```sh
    ./xml_processor decompress -i input.comp -o output.xml
    ```

6. **Convert XML to JSON**:

    ```sh
    ./xml_processor json -i input.xml -o output.json
    ```

7. **Draw Graph from XML**:

    ```sh
    ./xml_processor draw -i input.xml -o output.jpg
    ```

8. **Find Most Active User**:

    ```sh
    ./xml_processor most_active -i input.xml
    ```

9. **Find Most Influential User**:

    ```sh
    ./xml_processor most_influencer -i input.xml
    ```

10. **Find Mutual Followers**:

    ```sh
    ./xml_processor mutual -i input.xml -ids 1,2,3
    ```

11. **Suggest Users to Follow**:

    ```sh
    ./xml_processor suggest -i input.xml -id 1
    ```

12. **Search Posts**:

    ```sh
    ./xml_processor search -w word -i input.xml
    ./xml_processor search -t topic -i input.xml
    ```

### Graphical User Interface

The GUI version of the library can be integrated into applications to provide XML processing functionalities through a user-friendly interface.

## Data Structures

- `unordered_map<int, unordered_set<int>> adjList`: Stores user IDs and their followers.
- `unordered_map<int, string> userNames`: Maps user IDs to their names.
- **Stacks and Vectors**: Used for tracking XML tags and errors during consistency checks.

## Functions

### Helper Functions

- `bool lineEmpty(const string &line)`: Checks if a line is empty or contains only whitespace.
- [vector<int> parseStringToVector(const string &str)](http://_vscodecontentref_/0): Parses a string to a vector of numbers.
- `const char *getReqArg(int &i, int argc, char *argv[], const string &option)`: Gets the required argument for a command-line option.
- `string extractTagValue(const string &line, const string &tag)`: Extracts the value of a specific XML tag from a line.

### XML Consistency

- [void checkXMLConsistencyCMD(const string &inputFile, const string &outputFile, bool fixErrors)](http://_vscodecontentref_/1): Checks XML consistency and fixes errors for command line.
- [std::string checkXMLConsistencyGUI(const std::string &inputText, char flag)](http://_vscodecontentref_/2): Checks XML consistency and fixes errors for GUI.

### User Management

- [vector<int> getMutualFollowers(const vector<int> &ids)](http://_vscodecontentref_/3): Gets the mutual followers between users.
- [vector<int> suggestUsersToFollow(int userId)](http://_vscodecontentref_/4): Suggests users to follow.
- [void readXML(const string &fileName)](http://_vscodecontentref_/5): Reads the XML file and builds user and follower mappings.
- `void addUser(int id, const string &name)`: Adds a user.
- `void addFollower(int user, int follower)`: Adds a follower to a user.
- [pair<int, string> getMostActiveUser()](http://_vscodecontentref_/6): Gets the most active user based on followers.
- [pair<int, string> getMostInfluentialUser()](http://_vscodecontentref_/7): Gets the most influential user based on followers.

### Post Search

- [vector<string> postSearch(bool isCMD, const string &xmlContent, const string &searchTerm, bool isWord)](http://_vscodecontentref_/8): Searches posts by word or topic.

### XML Formatting

- [void prettifyXML(const string &inputFile, const string &outputFile)](http://_vscodecontentref_/9): Prettifies XML and saves to output file.
- [std::string prettifyXML(const std::string &inputFile)](http://_vscodecontentref_/10): Prettifies XML and returns as string for GUI.
- `string minifyXMLLine(const string &xmlContent)`: Minifies a single line of XML.
- [void minifyXMLFile(const string &inputFileName, const string &outputFileName)](http://_vscodecontentref_/11): Reads the XML file, minifies it, and saves it to another file.
- [string minifyXMLFile(const string &inputFileName)](http://_vscodecontentref_/12): Minifies XML content from a string for GUI.

### Compression

- [void compress(const string &filePath, const string &outputFilePath)](http://_vscodecontentref_/13): Compresses XML data.
- [void decompress(const string &inputFilePath, const string &outputFilePath)](http://_vscodecontentref_/14): Decompresses XML data.

## Complexity

- **Time Complexity**:
  - Parsing and searching operations: O(n) where n is the number of lines or elements.
  - User management operations: O(1) for insertion and lookup due to the use of hash maps.
- **Space Complexity**:
  - Dependent on the size of the XML data and the number of users and followers.

## References

- [C++ Standard Library Documentation](https://en.cppreference.com/w/)
- [Boost Library Documentation](https://www.boost.org/doc/libs/)
- [Regular Expressions in C++](https://www.regular-expressions.info/stdcpp.html)

This README provides an overview of the XML Processing Library, its features, usage instructions, and details about the data structures and functions used in the project.
