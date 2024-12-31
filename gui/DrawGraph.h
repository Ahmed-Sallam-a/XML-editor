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
#include <QString>
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
    void generateDOTFile(const QString& filename) const;
    static void generatePNG(const QString& dotFilename, const QString& pngFilename);
};

struct UserData {
    int userId;
    string userName;
    vector<string> posts;
    unordered_set<int> followers;

    UserData() : userId(-1) {}
};

void parseXMLAndBuildGraph(const string& xmlContent, Graph& graph);


#endif // DRAWGRAPH_H
