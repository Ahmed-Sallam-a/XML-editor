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

//------------------------Helper Functions------------------------//
bool lineEmpty(const std::string &line);
std::vector<int> parseStringToVector(const std::string &str);
const char *getReqArg(int &i, int argc, char *argv[], const std::string &option);
std::string extractTagValue(const std::string &line, const std::string &tag);

// Function to check XML consistency and fix errors
void checkXMLConsistencyCMD(const std::string &inputFile,
                            const std::string &outputFile,
                            bool fixErrors);
std::string checkXMLConsistencyGUI(const std::string &inputText, char flag);

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

// Functions to manage users and followers
void readXML(const std::string &fileName);
void addUser(int id, const std::string &name);
void addFollower(int user, int follower);

// Functions to minify XML
std::string minifyXMLLine(const std::string &xmlContent);
void minifyXMLFile(const std::string &inputFileName, const std::string &outputFileName);
std::string minifyXMLFile(const std::string &inputFileName); // For GUI

// Functions to Suggest users to follow and get mutual followers
std::vector<int> suggestUsersToFollow(int userId);
std::vector<int> getMutualFollowers(const std::vector<int> &ids);
// Function to find most influential user
std::pair<int, std::string> getMostInfluentialUser();

// functions to compress and decompress files
std::string parseXMLToString(const std::string &filePath);
void compress(const std::string &filePath, const std::string &outputFilePath);
void decompress(const std::string &inputFilePath, const std::string &outputFilePath);

// Global variables
// These are declared here and should be defined in exactly one source (.cpp) file.
extern std::unordered_map<int, std::unordered_set<int>> adjList; // User ID and their followers
extern std::unordered_map<int, std::string> userNames;           // User ID to name mapping

#endif // XML_EDITOR_H
