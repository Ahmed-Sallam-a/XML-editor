//
// Created by ahmed on 12/30/2024.
//

#ifndef XML_LIB_H
#define XML_LIB_H
#include <string>
#include <stack>
#include <vector>
#include <utility> // For std::pair
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <regex>
#include <memory>
#include <sstream>

// Namespace usage is avoided in headers to prevent potential naming conflicts.
// Use std:: prefix for standard library components.

// Function to check XML consistency and fix errors for command line
void checkXMLConsistencyCMD(const std::string &inputFile,
                            const std::string &outputFile,
                            bool fixErrors);

// Function to check XML consistency and fix errors for GUI
std::string checkXMLConsistencyGUI(const std::string &inputText, char flag);

const char *getReqArg(int &i, int argc, char *argv[], const std::string &option);

// Function to search posts by word or topic
std::vector<std::string> postSearch(bool isCMD,
                                    const std::string &xmlContent,
                                    const std::string &searchTerm,
                                    bool isWord);

// Functions to prettify XML
std::string prettifyXML(const std::string &inputFile); // For GUI
void prettifyXML(const std::string &inputFile, const std::string &outputFile);

// Function to get the most active user
std::pair<int, std::string> getMostActiveUser();

// Helper functions
bool lineEmpty(const std::string &line);

// Function to extract tag value from a line
std::string extractTagValue(const std::string &line, const std::string &tag);

// Functions to manage users and followers
void readXML(const std::string &fileName);
void addUser(int id, const std::string &name);
void addFollower(int user, int follower);

// Functions to minify XML
std::string minifyXMLLine(const std::string &xmlContent);
void minifyXMLFile(const std::string &inputFileName, const std::string &outputFileName);
std::string minifyXMLFile(const std::string &inputFileName); // For GUI

// Global variables
// These are declared here and should be defined in exactly one source (.cpp) file.
extern std::unordered_map<int, std::unordered_set<int>> adjList; // User ID and their followers
extern std::unordered_map<int, std::string> userNames;           // User ID to name mapping

#endif // XML_EDITOR_H
