#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;//std will be removed

// Graph class for social network representation
class Graph {
private:
    unordered_map<int, unordered_set<int>> adjList; // User ID and their followers    time complexity: O(1) for insert, find, erase
    unordered_map<int, string> userNames;          // User ID to name mapping    if collision occurs, time complexity: O(n) for insert, find, erase

public:
    void addUser(int id, const string &name) {
        userNames[id] = name;
        adjList[id]; // Initialize an empty set for the user
    }

    void addFollower(int user, int follower) {
        adjList[user].insert(follower);
    }

    pair<int, string> getMostInfluentialUser() {
        int maxFollowers = 0, mostInfluential = -1;
        for (const auto &entry : adjList) {
            if (entry.second.size() > maxFollowers) {
                maxFollowers = entry.second.size();
                mostInfluential = entry.first;
            }
        }
        return {mostInfluential, userNames[mostInfluential]};
    }

  
};


