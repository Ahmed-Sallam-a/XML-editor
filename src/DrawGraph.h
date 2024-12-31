
#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H
#include <sstream>
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <algorithm>


using namespace std;

// Define the User class
class User {
public:
    int userId;
    string name;
    vector<string> posts;
    unordered_set<int> followers;

    User(int id, const string& name);
    void addPost(const string& post);
    void addFollower(int followerId);
    void displayUser() const;
};

class Graph {
private:
    unordered_map<int, User> users;

public:
    void addUser(int userId, const string& name);
    void addPost(int userId, const string& post);
    void addFollower(int userId, int followerId);
    void displayGraph() const;
    void generateDOTFile(const string& filename) const;
};

struct UserData {
    int userId;
    string userName;
    vector<string> posts;
    unordered_set<int> followers;

    UserData() : userId(-1) {}
};

void parseXMLAndBuildGraph(const string& xmlContent, Graph& graph);
void generatePNG(const string& dotFilename, const string& pngFilename);
void processXMLToPNG(const string& xmlFilename, const string& pngFilename);

#endif // DRAWGRAPH_H
