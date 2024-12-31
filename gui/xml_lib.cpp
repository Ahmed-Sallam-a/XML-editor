//
// Created by ahmed on 12/30/2024.
//

#include "xml_lib.h"

// Using namespace std is allowed in source files
using namespace std;

// Definition of global variables
unordered_map<int, unordered_set<int>> adjList; // User ID and their followers
unordered_map<int, string> userNames;          // User ID to name mapping

// Helper function to check if a line is empty or contains only whitespace
bool lineEmpty(const string &line)
{
    return all_of(line.begin(), line.end(), [](char c)
                  { return isspace(c); });
}

// Helper function to get the required argument for a command-line option
const char *getReqArg(int &i, int argc, char *argv[], const string &option)
{
    if (i + 1 < argc && argv[i + 1][0] != '-')
        return argv[++i];

    else
    {
        cerr << "Error: " << option << " option requires an argument." << endl;
        exit(1);
    }
}

// Function to extract the value of a specific XML tag from a line
string extractTagValue(const string &line, const string &tag) {
    int start = line.find("<" + tag + ">");
    int end = line.find("</" + tag + ">");
    if (start == string::npos || end == string::npos) return "";
    start += tag.size() + 2;
    return line.substr(start, end - start);
}

// Function to check XML consistency and fix errors for command line
void checkXMLConsistencyCMD(const string &inputFile, const string &outputFile, bool fixErrors)
{
    // Stacks and vectors for tracking XML tags and errors
    stack<char> tags;
    stack<string> s;
    vector<int> errors;
    stack<string> wrong;

    ifstream file(inputFile);

    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    int lineNumber = 0, i = 0, j = 0, jLN, count = 0;
    vector<string> output;
    while (getline(file, line))
    {
        if (lineEmpty(line))
            continue;
        lineNumber++;
        i = 0;
        while (line[i])
        {
            if (line[i] == '<')
            {
                if (!tags.empty())
                {
                    int k = i + 1;
                    // First case: <....x        </....>
                    if (line[k] == '/')
                    {
                        while (line[k] != '>')
                        {
                            k++;
                        }
                        output[jLN - 1].insert(j + k - i - 1, 1, '>');
                        s.push(output[jLN - 1].substr(j + 1, k - i - 2));
                        errors.push_back(jLN);
                        count++;
                    }
                    // Second case: </....x      <****> && <....x  <....>
                    else
                    {
                        int k = i - 1;
                        if (jLN == lineNumber)
                        {
                            while (!(line[k] != ' '))
                                k--;
                            line.insert(k + 1, 1, '>');
                            s.pop();
                            errors.push_back(lineNumber);
                            count--;
                        }
                        else
                        {
                            k = output[jLN - 1].size();
                            output[jLN - 1].insert(k, 1, '>');
                            while (output[jLN - 1][--k] != '/' && k != -1)
                                ;
                            if (k == -1)
                            {
                                s.push(output[jLN - 1].substr(j + 1, output[jLN - 1].size() - j - 2));
                            }
                            else
                                s.pop();
                            errors.push_back(jLN);
                            count--;
                        }
                    }
                    tags.pop();
                }
                // Third case: right sequence
                if (tags.empty())
                    tags.push('<');
                j = i, jLN = lineNumber;
            }
            if (line[i] == '>')
            {
                if (tags.empty())
                {
                    int k = i;
                    i++;
                    while (line[k] != '/' && k != -1)
                        k--;
                    // First case: <....>     x/0...> && <....>  x....>
                    if (line[k] == '/')
                    {
                        line.insert(k, 1, '<');
                        s.pop();
                        errors.push_back(lineNumber);
                        count--;
                    }
                    // Second case: x....>        </....>
                    else if (k == -1)
                    {
                        while (line[++k] == '\t')
                            ;
                        line.insert(k, 1, '<');
                        s.push(line.substr(k + 1, i - k - 1));
                        errors.push_back(lineNumber);
                        count++;
                    }
                }
                else if (tags.top() == '<')
                    tags.pop();
                string s1;
                if (line[j + 1] == '/')
                {
                    s1 = line.substr(j + 2, i - j - 2);
                    if (s1 == s.top())
                    {
                        s.pop();
                        count--;
                    }
                    else
                    {
                        errors.push_back(lineNumber);
                        wrong.push(s1);
                        line = line.substr(0, line.size() - s1.size() - 3);
                    }
                }
                else
                {
                    s1 = line.substr(j + 1, i - j - 1);
                    s.push(s1);
                    count++;
                }
            }
            if ((!s.empty()) && (!wrong.empty()) && (s.top() == wrong.top()))
            {
                string s2 = "";
                count -= 2;
                while (count--)
                    s2 += "\t";
                s2 = s2 + "</" + s.top() + ">";
                output.push_back(line);
                line = s2;
                lineNumber++;
                wrong.pop();
                i = -1;
            }
            i++;
        }
        output.push_back(line);
    }

    file.close();
    if (!errors.empty())
    {
        cout << "Invalid XML detected with errors in lines: ";
        for (int errorLine : errors)
            cout << errorLine << " ";
        cout << endl;

        if (fixErrors && !outputFile.empty())
        {
            ofstream outFile(outputFile);
            if (outFile.is_open())
            {
                for (const auto &fixedLine : output)
                {
                    outFile << fixedLine << endl;
                }
                outFile.close();
                cout << "Errors fixed. Corrected XML written to: " << outputFile << endl;
            }
            else
            {
                cerr << "Failed to open output file: " << outputFile << endl;
            }
        }
    }
    else
        cout << "The XML File is valid." << endl;
}

// Function to check XML consistency and fix errors for GUI
std::string checkXMLConsistencyGUI(const std::string &inputText, char flag)
{
    // Stacks and vectors for tracking XML tags and errors
    stack<char> tags;
    stack<string> s;
    vector<int> errors;
    stack<string> wrong;

    istringstream stream(inputText);

    string line;
    int lineNumber = 0, i = 0, j = 0, jLN, count = 0;
    vector<string> output;
    while (getline(stream, line))
    {
        if (lineEmpty(line))
            continue;
        lineNumber++;
        i = 0;
        while (line[i])
        {
            if (line[i] == '<')
            {
                if (!tags.empty())
                {
                    int k = i + 1;
                    // First case: <....x        </....>
                    if (line[k] == '/')
                    {
                        while (line[k] != '>')
                        {
                            k++;
                        }
                        output[jLN - 1].insert(j + k - i - 1, 1, '>');
                        s.push(output[jLN - 1].substr(j + 1, k - i - 2));
                        errors.push_back(jLN);
                        count++;
                    }
                    // Second case: </....x      <****> && <....x  <....>
                    else
                    {
                        int k = i - 1;
                        if (jLN == lineNumber)
                        {
                            while (!(line[k] != ' '))
                                k--;
                            line.insert(k + 1, 1, '>');
                            s.pop();
                            errors.push_back(lineNumber);
                            count--;
                        }
                        else
                        {
                            k = output[jLN - 1].size();
                            output[jLN - 1].insert(k, 1, '>');
                            while (output[jLN - 1][--k] != '/' && k != -1)
                                ;
                            if (k == -1)
                            {
                                s.push(output[jLN - 1].substr(j + 1, output[jLN - 1].size() - j - 2));
                            }
                            else
                                s.pop();
                            errors.push_back(jLN);
                            count--;
                        }
                    }
                    tags.pop();
                }
                // Third case: right sequence
                if (tags.empty())
                    tags.push('<');
                j = i, jLN = lineNumber;
            }
            if (line[i] == '>')
            {
                if (tags.empty())
                {
                    int k = i;
                    i++;
                    while (line[k] != '/' && k != -1)
                        k--;
                    // First case: <....>     x/0...> && <....>  x....>
                    if (line[k] == '/')
                    {
                        line.insert(k, 1, '<');
                        s.pop();
                        errors.push_back(lineNumber);
                        count--;
                    }
                    // Second case: x....>        </....>
                    else if (k == -1)
                    {
                        while (line[++k] == '\t')
                            ;
                        line.insert(k, 1, '<');
                        s.push(line.substr(k + 1, i - k - 1));
                        errors.push_back(lineNumber);
                        count++;
                    }
                }
                else if (tags.top() == '<')
                    tags.pop();
                string s1;
                if (line[j + 1] == '/')
                {
                    s1 = line.substr(j + 2, i - j - 2);
                    if (s1 == s.top())
                    {
                        s.pop();
                        count--;
                    }
                    else
                    {
                        errors.push_back(lineNumber);
                        wrong.push(s1);
                        line = line.substr(0, line.size() - s1.size() - 3);
                    }
                }
                else
                {
                    s1 = line.substr(j + 1, i - j - 1);
                    s.push(s1);
                    count++;
                }
            }
            if ((!s.empty()) && (!wrong.empty()) && (s.top() == wrong.top()))
            {
                string s2 = "";
                count -= 2;
                while (count--)
                    s2 += "\t";
                s2 = s2 + "</" + s.top() + ">";
                output.push_back(line);
                line = s2;
                lineNumber++;
                wrong.pop();
                i = -1;
            }
            i++;
        }
        output.push_back(line);
    }
    if (!errors.empty())
    {
        if (flag == 'f')
        {
            string out = "";
            for (const auto &fixedLine : output)
            {
                out += fixedLine;
                out += '\n';
            }
            return out;
        }
        else if (flag == 'c')
        {
            string out = "";
            for (int errorLine : errors)
            {
                out += to_string(errorLine) + " ";
            }
            return out;
        }
    }
    else
        return "The XML File is valid.";
    return "";
}

// Function to search posts by word or topic
std::string postSearch(bool isCMD, const string &xmlContent, const string &searchTerm, bool isWord)
{   string out="";
    string line;
    vector<string> matchingPosts;
    bool inPost = false;

    string currentPost;
    string printedPost;

    string bodyPattern = R"(<body>.*)" + searchTerm + R"(.*</body>)";
    regex wordRegex(bodyPattern, regex_constants::icase);

    string topicPattern = "<topic>\\s*" + searchTerm + "\\s*</topic>";
    regex topicRegex(topicPattern);

    unique_ptr<istream> inputStream;
    if (isCMD)
    {
        inputStream = make_unique<ifstream>(xmlContent);
        if (!static_cast<ifstream *>(inputStream.get())->is_open())
        {
            cerr << "Error opening file!" << endl;
            return "Error opening file!";
        }
    }
    else
    {
        inputStream = make_unique<stringstream>(xmlContent);
    }

    while (getline(*inputStream, line))
    {
        if (line.find("<post>") != string::npos)
        {
            inPost = true;
            currentPost.clear();
            printedPost.clear();
        }

        if (inPost)
        {
            currentPost += line;
            printedPost += line + "\n";
        }

        if (line.find("</post>") != string::npos)
        {
            inPost = false;
            if ((isWord && regex_search(currentPost, wordRegex)) ||
                (!isWord && regex_search(currentPost, topicRegex)))
                matchingPosts.push_back(printedPost);
        }
    }

    if (matchingPosts.empty()){
        string type = (isWord ? "word" : "topic");
        out= "No posts found containing the "+ type+ ": " + searchTerm+"\n" ;
    }
    else
    {   string type=(isWord ? "word" : "topic");
        out= "Posts containing the " + type + ": " + searchTerm + "\n";
        for (const auto &post : matchingPosts){
            out+=post;
            out+="\n";
        }
    }
    return out;
}

// Function to prettify XML and save to output file
void prettifyXML(const string& inputFile, const string& outputFile) {
    ifstream input(inputFile);
    ofstream outputStream(outputFile);

    if (!input.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return;
    }

    if (!outputStream.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        return;
    }

    string line;
    int indentLevel = 0;
    while (getline(input, line)) {

        if (line.empty()) continue; // Skip empty lines

        int pos = 0;
        bool firstFlag=false, secondFlag=false;
        while (pos < line.size()) {
            if (line[pos] == '<') {

                if(firstFlag) secondFlag=true;
                else if(!firstFlag&&!secondFlag) firstFlag=true;


                int endPos = line.find('>', pos);
                if (endPos == string::npos) break;

                string tag = line.substr(pos, endPos - pos + 1);

                // Handle closing tags
                if (tag[1] == '/') {
                    indentLevel--;
                }

                if (!secondFlag){
                    // Write the tag with proper indentation
                    for (int i = 0; i < indentLevel; ++i) {
                        outputStream << "  ";
                    }
                }

                outputStream << tag ;

                // Handle opening tags (not self-closing)
                if (tag[1] != '/' && tag[tag.size() - 2] != '/') {
                    indentLevel++;
                }

                pos = endPos + 1;
            } else {
                // Handle text content between tags
                int nextTagPos = line.find('<', pos);
                string text = line.substr(pos, nextTagPos - pos);


                if (!text.empty()) {
                    outputStream << text ;
                }

                pos = nextTagPos ;
            }
        }
        outputStream << endl;
    }

    input.close();
    outputStream.close();

    cout << "Formatted XML has been saved to: " << outputFile << endl;
}

// Function to prettify XML and return as string for GUI
std::string prettifyXML(const std::string& inputFile) {

    istringstream stream(inputFile);

    string line;
    string output;
    int indentLevel = 0;
    while (getline(stream, line)) {

        if (line.empty()) continue; // Skip empty lines

        int pos = 0;
        bool firstFlag=false, secondFlag=false;
        while (pos < line.size()) {
            if (line[pos] == '<') {

                if(firstFlag) secondFlag=true;
                else if(!firstFlag&&!secondFlag) firstFlag=true;


                int endPos = line.find('>', pos);
                if (endPos == string::npos) break;

                string tag = line.substr(pos, endPos - pos + 1);

                // Handle closing tags
                if (tag[1] == '/') {
                    indentLevel--;
                }

                if (!secondFlag){
                    // Write the tag with proper indentation
                    for (int i = 0; i < indentLevel; ++i) {
                        output += "  ";
                    }
                }

                output += tag ;

                // Handle opening tags (not self-closing)
                if (tag[1] != '/' && tag[tag.size() - 2] != '/') {
                    indentLevel++;
                }

                pos = endPos + 1;
            } else {
                // Handle text content between tags
                int nextTagPos = line.find('<', pos);
                string text = line.substr(pos, nextTagPos - pos);


                if (!text.empty()) {
                    output +=  text ;
                }

                pos = nextTagPos ;
            }
        }
        output += "\n";
    }


    cout << "Formatted XML has been processed for GUI." << endl;
    return output;
}

// Function to read the XML file and build user and follower mappings
void parse_string(string input)
{
    stringstream ss(input);
    string line;
    int currentUserId = -1;
    while (getline(ss, line))
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
        else if (line.find("</user>") != string::npos)
            currentUserId = -1;
    }
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
        // Check ID tag
        if (line.find("<id>") != string::npos)
        {
            int id = stoi(extractTagValue(line, "id"));
            // Assign the new user
            if (currentUserId == -1)
                currentUserId = id;

            // Adding follower to the current user
            else
                adjList[currentUserId].insert(id);
        }
        // Check name tag
        else if (line.find("<name>") != string::npos)
        {
            // Mapping the current user id to the name
            string name = extractTagValue(line, "name");
            userNames[currentUserId] = name;
        }
        // Reset for new user
        else if (line.find("</user>")!= string::npos)
            currentUserId = -1;

    }
    file.close();
}

// Function to add a user
void addUser(int id, const string &name) {
    userNames[id] = name;
    adjList[id]; // Initialize an empty set for the user
}

// Function to add a follower to a user
void addFollower(int user, int follower) {
    adjList[user].insert(follower);
}

// Function to get the most active user based on followers
pair<int, string> getMostActiveUser() {
    int maxConnections = 0, mostActive = -1;
    for (const auto &entry : adjList) {
        int connections = entry.second.size();
        for (const auto &user : adjList) {
            if (user.second.count(entry.first)) connections++;
        }
        if (connections > maxConnections || (connections == maxConnections && (mostActive == -1 || entry.first < mostActive))) {
            maxConnections = connections;
            mostActive = entry.first;
        }
    }
    if (mostActive != -1)
        return {mostActive, userNames[mostActive]};
    else
        return {-1, ""};
}

// Function to minify a single line of XML
string minifyXMLLine(const string &xmlContent) {
    string minified;
    bool insideTag = false;

    // Iterate through each character in the line
    for (size_t i = 0; i < xmlContent.size(); ++i) {
        char currentChar = xmlContent[i];

        // If the current character is part of a tag (i.e., '<' or '>')
        if (currentChar == '<') {
            insideTag = true;
        }
        else if (currentChar == '>') {
            insideTag = false;
        }

        // If we're not inside a tag, skip unnecessary whitespaces and newlines
        if (!insideTag) {
            if (isspace(currentChar)) {
                // Skip spaces outside of tags
                continue;
            }
        }
        // Append the current character to the minified result
        minified += currentChar;
    }

    return minified;
}

// Function to read the XML file, minify it, and save it to another file
void minifyXMLFile(const string &inputFileName, const string &outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    // To hold the content of the XML file
    string minifiedContent;
    string line;

    // Read the file line by line
    while (getline(inputFile, line)) {
        // Minify each line and append to the result
        string minifiedLine = minifyXMLLine(line);
        minifiedContent += minifiedLine + "\n";
    }

    inputFile.close();  // Close the input file

    // Write the minified content to the output file
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    outputFile << minifiedContent;  // Write the minified content to the output file
    outputFile.close();  // Close the output file

    cout << "Minification successful! Saved to: " << outputFileName << endl;
}

// Function to minify XML content from a string for GUI
string minifyXMLFile(const string &inputFileName) {

    istringstream stream (inputFileName);

    // To hold the content of the XML file
    string minifiedContent;
    string line;

    // Read the file line by line
    while (getline(stream, line)) {
        // Minify each line and append to the result
        string minifiedLine = minifyXMLLine(line);
        minifiedContent += minifiedLine + "\n";
    }
    return minifiedContent;
}
pair<string, string> getMostInfluentialUser()
{
    int maxFollowers = 0, mostInfluential = -1;
    for (const auto &entry : adjList)
    {
        if (entry.second.size() > maxFollowers)
        {
            maxFollowers = entry.second.size();
            mostInfluential = entry.first;
        }
    }
    string mostInfluential_string = to_string(mostInfluential);

    return {mostInfluential_string, userNames[mostInfluential]};
}
vector<int> getMutualFollowers(const vector<int> &ids) {
    if (ids.empty()) return {};
    unordered_set<int> mutualFollowers = adjList[ids[0]];
    for (size_t i = 1; i < ids.size(); ++i) {
        unordered_set<int> currentFollowers = adjList[ids[i]];
        for (auto it = mutualFollowers.begin(); it != mutualFollowers.end();) {
            if (currentFollowers.find(*it) == currentFollowers.end())
                it = mutualFollowers.erase(it);
            else
                ++it;
        }
    }
    return vector<int>(mutualFollowers.begin(), mutualFollowers.end());
}

// Function to suggest users to followers
vector<int> suggestUsersToFollow(int userId) {
    unordered_set<int> suggestions;
    for (int follower : adjList[userId]) {
        for (int followerOfFollower : adjList[follower]) {
            if (followerOfFollower != userId && !adjList[userId].count(followerOfFollower)) {
                suggestions.insert(followerOfFollower);
            }
        }
    }
    return vector<int>(suggestions.begin(), suggestions.end());
}

