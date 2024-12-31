#include "DrawGraph.h"

// User class implementations
User::User(int id, const string& name) : userId(id), name(name) {}

void User::addPost(const string& post) {
    posts.push_back(post);
}

void User::addFollower(int followerId) {
    followers.insert(followerId);
}

void User::displayUser() const {
    cout << "User ID: " << userId << ", Name: " << name << "\n";
    cout << "Posts:\n";
    for(const string& post : posts) {
        cout << post << "\n";
    }
    cout << "Followers: ";
    for(int followerId : followers) {
        cout << followerId << " ";
    }
    cout << "\n\n";
}

// Graph class implementations
void Graph::addUser(int userId, const string& name) {
    users.emplace(userId, User(userId, name));
}

void Graph::addPost(int userId, const string& post) {
    auto it = users.find(userId);
    if(it != users.end()) {
        it->second.addPost(post);
    }
}

void Graph::addFollower(int userId, int followerId) {
    auto it = users.find(userId);
    if(it != users.end()) {
        it->second.addFollower(followerId);
    }
}

void Graph::displayGraph() const {
    for(const auto& pair : users) {
        pair.second.displayUser();
    }
}

void Graph::generateDOTFile(const string& filename) const {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Start DOT file with styling
    dotFile << "digraph SocialNetwork {\n"
            << "    bgcolor=\"#FFFFFF\";\n"
            << "    rankdir=LR;\n"
            << "    node [\n"
            << "        shape=circle,\n"
            << "        style=filled,\n"
            << "        fillcolor=\"#ADD8E6\",\n"
            << "        fontname=\"Arial\",\n"
            << "        fontsize=10,\n"
            << "        width=1,\n"
            << "        height=1\n"
            << "    ];\n"
            << "    edge [\n"
            << "        color=\"#4169E1\",\n"
            << "        penwidth=1.5,\n"
            << "        arrowsize=0.8\n"
            << "    ];\n";

    // Add nodes with HTML-like labels
    for (const auto& pair : users) {
        const User& user = pair.second;
        string escapedName = user.name;
        replace(escapedName.begin(), escapedName.end(), '"', '\'');

        // Create HTML-like label with user info
        dotFile << "    " << user.userId << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"0\">"
               << "<TR><TD><B>ID: " << user.userId << "</B></TD></TR>"
               << "<TR><TD>" << escapedName << "</TD></TR>";

        // Add post count
        dotFile << "<TR><TD>Posts: " << user.posts.size() << "</TD></TR>";

        dotFile << "</TABLE>>];\n";
    }

    // Add edges with labels
    for (const auto& pair : users) {
        const User& user = pair.second;
        for (int followerId : user.followers) {
            dotFile << "    " << user.userId << " -> " << followerId
                   << " [label=\"follows\"];\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();
}

void parseXMLAndBuildGraph(const string& xmlContent, Graph& graph) {
    stringstream ss(xmlContent);
    string line;
    vector<UserData> usersData;
    UserData currentUser;
    bool inFollowers = false;

    while (getline(ss, line)) {
        // Trim whitespace
        size_t first = line.find_first_not_of(" \t\n\r");
        size_t last = line.find_last_not_of(" \t\n\r");
        if (first == string::npos) continue; // Skip empty lines
        line = line.substr(first, (last - first + 1));

        if(line.find("<user>") != string::npos) {
            currentUser = UserData();
        }
        else if(line.find("</user>") != string::npos) {
            if(currentUser.userId != -1 && !currentUser.userName.empty()) {
                usersData.push_back(currentUser);
            }
        }
        else if(line.find("<id>") != string::npos && !inFollowers) {
            size_t start = line.find("<id>") + 4;
            size_t end = line.find("</id>");
            if(start != string::npos && end != string::npos) {
                currentUser.userId = stoi(line.substr(start, end - start));
            }
        }
        else if(line.find("<name>") != string::npos) {
            size_t start = line.find("<name>") + 6;
            size_t end = line.find("</name>");
            if(start != string::npos && end != string::npos) {
                currentUser.userName = line.substr(start, end - start);
            }
        }
        else if(line.find("<body>") != string::npos) {
            size_t start = line.find("<body>") + 6;
            size_t end = line.find("</body>");
            if(start != string::npos && end != string::npos) {
                currentUser.posts.push_back(line.substr(start, end - start));
            }
        }
        else if(line.find("<followers>") != string::npos) {
            inFollowers = true;
        }
        else if(line.find("</followers>") != string::npos) {
            inFollowers = false;
        }
        else if(line.find("<id>") != string::npos && inFollowers) {
            size_t start = line.find("<id>") + 4;
            size_t end = line.find("</id>");
            if(start != string::npos && end != string::npos) {
                int followerId = stoi(line.substr(start, end - start));
                currentUser.followers.insert(followerId);
            }
        }
    }


    // First pass: Add all users
    for(const auto& userData : usersData) {
        graph.addUser(userData.userId, userData.userName);

        // Add posts
        for(const auto& post : userData.posts) {
            graph.addPost(userData.userId, post);
        }
    }

    // Second pass: Add all follower relationships
    for(const auto& userData : usersData) {
        for(int followerId : userData.followers) {
            graph.addFollower(userData.userId, followerId);
        }
    }
}

void generatePNG(const string& dotFilename, const string& pngFilename) {
    string command = "dot -Tpng " + dotFilename + " -o " + pngFilename;
    int result = system(command.c_str());
    if (result == 0) {
        cout << "Successfully generated " << pngFilename << endl;
    } else {
        cerr << "Failed to generate PNG file" << endl;
    }
}

void processXMLToPNG(const string& xmlFilename, const string& pngFilename) {
    string dotFilename = "temp.dot"; // Temporary DOT file

    // Read XML content
    ifstream xmlFile(xmlFilename);
    if (!xmlFile.is_open()) {
        cerr << "Failed to open XML file: " << xmlFilename << endl;
        return;
    }
    stringstream xmlBuffer;
    xmlBuffer << xmlFile.rdbuf();
    string xmlContent = xmlBuffer.str();
    xmlFile.close();

    // Build graph from XML content
    Graph graph;
    parseXMLAndBuildGraph(xmlContent, graph);

    // Generate DOT file
    graph.generateDOTFile(dotFilename);

    // Generate PNG
    generatePNG(dotFilename, pngFilename);

    // Open the PNG file
#ifdef _WIN32
    string command = "start " + pngFilename;
#elif __APPLE__
    string command = "open " + pngFilename;
#else
    string command = "xdg-open " + pngFilename;
#endif
    system(command.c_str());
}

