#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;//std will be removed


    unordered_map<int, unordered_set<int>> adjList; // User ID and their followers    time complexity: O(1) for insert, find, erase
    unordered_map<int, string> userNames;    
    
        string extractTagValue(const string &line, const string &tag) {
        int start = line.find("<" + tag + ">") ;
        int end = line.find("</" + tag + ">");
        if (start == string::npos || end == string::npos) return "";
        start += tag.size() + 2;
        return line.substr(start,end-start);
    }

    void readXML(const string &fileName){
        ifstream file (fileName);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << fileName << endl;
            return;
        }
        string line;
        int currentUserId = -1;
        while (getline(file,line))
        {
            // check ID tag
            if (line.find("<id>") != string::npos)
            {
                int id = stoi(extractTagValue(line, "id"));
                // assign the new user
                if (currentUserId == -1)  
                    currentUserId = id; 

                // adding follower to the current user    
                else 
                    adjList[currentUserId].insert(id);
            }
            // check name tag
            else if (line.find("<name>") != string::npos)
            {
                // mapping the current user id to the name
                string name = extractTagValue(line, "name");
                userNames[currentUserId] = name;
            }
            // reset for new user 
            else if (line.find("</user>")!= string::npos)
                currentUserId = -1;

        }
        file.close();
    }     // User ID to name mapping    if collision occurs, time complexity: O(n) for insert, find, erase

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

  int main(int argc, char const *argv[]) {

    if (argc != 4) {
        cerr << "Usage: xml_editor most_influential -i input_file.xml" << endl;
        return 1;
    }

    // Check the command and arguments
    string command = argv[1];
    string inputFlag = argv[2];
    string inputFile = argv[3];

    if (command != "most_influential" || inputFlag != "-i") {
        cerr << "Invalid command or flags. Usage: xml_editor most_influential -i input_file.xml" << endl;
        return 1;
    }
    readXML(inputFile);
    cout << "Most influential User: " << getMostInfluentialUser().second
         << " (ID: " << getMostInfluentialUser().first << ")" << endl;
    
    return 0;
    
}
  
  



