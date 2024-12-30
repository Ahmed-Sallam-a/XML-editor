#include "DrawGraph.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>

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

// Helper function to escape special characters in labels
QString escapeString(const QString& input) {
    QString escaped = input;
    escaped.replace("\\", "\\\\"); // Escape backslashes
    escaped.replace("\"", "\\\""); // Escape double quotes
    escaped.replace("<", "\\<");
    escaped.replace(">", "\\>");
    // Add more replacements as needed
    return escaped;
}

void Graph::generateDOTFile(const QString& filename) const {
    QFile dotFile(filename);
    if (!dotFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open DOT file for writing:" << filename;
        QMessageBox::warning(nullptr, "Error", "Cannot open file for writing:\n" + filename);
        return;
    }

    QTextStream out(&dotFile);

    // Start DOT file with styling
    out << "digraph SocialNetwork {\n"
           "    bgcolor=\"#FFFFFF\";\n"
           "    rankdir=LR;\n"
           "    node [\n"
           "        shape=circle,\n"
           "        style=filled,\n"
           "        fillcolor=\"#ADD8E6\",\n"
           "        fontname=\"Arial\",\n"
           "        fontsize=10,\n"
           "        width=1,\n"
           "        height=1\n"
           "    ];\n"
           "    edge [\n"
           "        color=\"#4169E1\",\n"
           "        penwidth=1.5,\n"
           "        arrowsize=0.8\n"
           "    ];\n";

    // Add nodes with HTML-like labels
    for (const auto& pair : users) {
        const User& user = pair.second;
        QString escapedName = escapeString(QString::fromStdString(user.name));

        // Create HTML-like label with user info
        out << "    " << QString::number(user.userId) << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"0\">"
                "<TR><TD><B>ID: " << QString::number(user.userId) << "</B></TD></TR>"
                "<TR><TD>" << escapedName << "</TD></TR>"
                "<TR><TD>Posts: " << QString::number(user.posts.size()) << "</TD></TR>"
                "</TABLE>>];\n";
    }

    // Add edges with labels
    for (const auto& pair : users) {
        const User& user = pair.second;
        for (int followerId : user.followers) {
            out << "    " << QString::number(user.userId) << " -> " << QString::number(followerId)
                << " [label=\"follows\"];\n";
        }
    }

    out << "}\n";
    dotFile.close();

    qDebug() << "DOT file generated successfully at:" << filename;
}

    void Graph::generatePNG(const QString& dotFilename, const QString& pngFilename){
    // Verify that the DOT file exists
    QFileInfo dotFileInfo(dotFilename);
    if (!dotFileInfo.exists()) {
        qWarning() << "DOT file does not exist:" << dotFilename;
        QMessageBox::warning(nullptr, "File Not Found", "The specified DOT file does not exist:\n" + dotFilename);
        return;
    }

    // Check if 'dot' executable is available in the system PATH
    QString dotExecutable = "dot"; // Assumes 'dot' is in PATH
    // To specify a path, e.g., QString dotExecutable = "C:/Program Files/Graphviz/bin/dot.exe";

    // Prepare arguments for the 'dot' command
    QStringList arguments;
    arguments << "-Tpng" << dotFilename << "-o" << pngFilename;

    // Initialize QProcess
    QProcess process;
    process.setProgram(dotExecutable);
    process.setArguments(arguments);
    process.setProcessChannelMode(QProcess::MergedChannels); // Combine stdout and stderr

    // Start the process
    process.start();

    // Wait for the process to finish, with a timeout (e.g., 10 seconds)
    if (!process.waitForFinished(10000)) { // 10000 milliseconds = 10 seconds
        qWarning() << "Graphviz 'dot' process timed out.";
        QMessageBox::warning(nullptr, "Process Timeout", "The Graphviz 'dot' process timed out.");
        process.kill(); // Terminate the process
        return;
    }

    // Check the exit status
    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        QString errorOutput = process.readAll();
        qWarning() << "Failed to generate PNG file:" << errorOutput;
        QMessageBox::critical(nullptr, "Generation Failed", "Failed to generate PNG file:\n" + errorOutput);
        return;
    }

    qDebug() << "Successfully generated" << pngFilename;
    QMessageBox::information(nullptr, "Success", "PNG file generated successfully:\n" + pngFilename);
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
