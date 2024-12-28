#include <bits/stdc++.h>

using namespace std;

// Function to check XML consistency and fix errors for command line
void checkXMLConsistencyCMD(const string &inputFile, const string &outputFile, bool fixErrors);
// Function to check XML consistency and fix errors for GUI
string checkXMLConsistencyGUI(const string &inputText, char flag);

// Function to search posts by word or topic
void postSearch(const bool isCMD, const string &xmlContent, const string &searchTerm, bool isWord);

// Helper functions
bool lineEmpty(const string &line)
{
    return all_of(line.begin(), line.end(), [](char c)
                  { return isspace(c); });
}
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

// Main function
int main(int argc, char *argv[])
{
    // Available commands
    if (argc < 2)
    {
        cerr << "\033[1m\033[31mUsage:\033[0m xml_editor <command> [options]" << endl;
        cerr << "\033[1m\033[34mCommands:\033[0m" << endl;
        cerr << "  \033[1mverify\033[0m           -i input_file.xml [-f] [-o output_file.xml]" << endl;
        cerr << "  \033[1mformat\033[0m           -i input_file.xml -o output_file.xml" << endl;
        cerr << "  \033[1mjson\033[0m             -i input_file.xml -o output_file.json" << endl;
        cerr << "  \033[1mmini\033[0m             -i input_file.xml -o output_file.xml" << endl;
        cerr << "  \033[1mcompress\033[0m         -i input_file.xml -o output_file.comp" << endl;
        cerr << "  \033[1mdecompress\033[0m       -i input_file.comp -o output_file.xml" << endl;
        cerr << "  \033[1mdraw\033[0m             -i input_file.xml -o output_file.jpg" << endl;
        cerr << "  \033[1mmost_active\033[0m      -i input_file.xml" << endl;
        cerr << "  \033[1mmost_influencer\033[0m  -i input_file.xml" << endl;
        cerr << "  \033[1mmutual\033[0m           -i input_file.xml -ids 1,2,3" << endl;
        cerr << "  \033[1msuggest\033[0m          -i input_file.xml -id 1" << endl;
        cerr << "  \033[1msearch\033[0m           -w word -i input_file.xml" << endl;
        cerr << "                   -t topic -i input_file.xml" << endl;
        return 1;
    }

    string inputFile, outputFile, searchTerm;
    string command = argv[1];
    bool fixErrors = false;
    bool isWordSearch = true;

    // Parse command line arguments
    for (int i = 2; i < argc; ++i)
    {
        string arg = argv[i];

        if (arg == "-i")
            inputFile = getReqArg(i, argc, argv, "-i");

        else if (arg == "-o")
            outputFile = getReqArg(i, argc, argv, "-o");

        else if (arg == "-w")
            searchTerm = getReqArg(i, argc, argv, "-w");

        else if (arg == "-t")
        {
            searchTerm = getReqArg(i, argc, argv, "-t");
            isWordSearch = false;
        }
        else if (arg == "-f")
            fixErrors = true;

        else
        {
            cerr << "Unknown option: " << arg << endl;
            return 1;
        }
    }

    // Execute the command
    if (command == "search")
        postSearch(true, inputFile, searchTerm, isWordSearch);

    else if (command == "verify")
    {
        checkXMLConsistencyCMD(inputFile, outputFile, fixErrors);
    }
    else if (command == "format")
    {
        // Implement format functionality
    }
    else if (command == "json")
    {
        // Implement json functionality
    }
    else if (command == "mini")
    {
        // Implement mini functionality
    }
    else if (command == "compress")
    {
        // Implement compress functionality
    }
    else if (command == "decompress")
    {
        // Implement decompress functionality
    }
    else if (command == "draw")
    {
        // Implement draw functionality
    }
    else if (command == "most_active")
    {
        // Implement most_active functionality
    }
    else if (command == "most_influencer")
    {
        // Implement most_influencer functionality
    }
    else if (command == "mutual")
    {
        // Implement mutual functionality
    }
    else if (command == "suggest")
    {
        // Implement suggest functionality
    }
    else
    {
        cerr << "Unknown command: " << command << endl;
        return 1;
    }

    return 0;
}

void checkXMLConsistencyCMD(const string &inputFile, const string &outputFile, bool fixErrors)
{
    // stacks and vectors
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
                    // first case: <....x        </....>
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
                    // second case: </....x      <****> && <....x  <....>
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
                // third case: right sequence
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
                    // first case: <....>     x/0...> && <....>  x....>
                    if (line[k] == '/')
                    {
                        line.insert(k, 1, '<');
                        s.pop();
                        errors.push_back(lineNumber);
                        count--;
                    }
                    // second case: x....>        </....>
                    else if (k == -1)
                    {
                        while (line[++k] == '\t')
                            ;
                        line.insert(k, 1, '<');
                        s.push(line.substr(k + 1, i - k - 1));
                        // cout<<s.top()<<" <<<<<<";
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
                //////////////////////s.pop();
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

string checkXMLConsistencyGUI(const string &inputText, char flag)
{
    // stacks and vectors
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
                    // first case: <....x        </....>
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
                    // second case: </....x      <****> && <....x  <....>
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
                // third case: right sequence
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
                    // first case: <....>     x/0...> && <....>  x....>
                    if (line[k] == '/')
                    {
                        line.insert(k, 1, '<');
                        s.pop();
                        errors.push_back(lineNumber);
                        count--;
                    }
                    // second case: x....>        </....>
                    else if (k == -1)
                    {
                        while (line[++k] == '\t')
                            ;
                        line.insert(k, 1, '<');
                        s.push(line.substr(k + 1, i - k - 1));
                        // cout<<s.top()<<" <<<<<<";
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
            for (const auto &line : output)
            {
                out += line;
                out += '\n';
            }
            return out;
        }
        else if (flag == 'c')
        {
            string out = "";
            for (int errorLine : errors)
            {
                out += errorLine;
                out += " ";
            }
        }
    }
    else
        return "The XML File is valid.";
    return "";
}

void postSearch(const bool isCMD, const string &xmlContent, const string &searchTerm, bool isWord)
{

    string line;
    vector<string> matchingPosts;
    bool inPost = false;

    string currentPost;
    string printedPost;

    string bodyPattern = R"(<body>.*)" + searchTerm + R"(.*</body>)";
    regex word(bodyPattern, regex_constants::icase);

    string topicPattern = "<topic>\\s*" + searchTerm + "\\s*</topic>";
    regex topic(topicPattern);

    unique_ptr<istream> inputStream;
    if (isCMD)
    {
        inputStream = make_unique<ifstream>(xmlContent);
        if (!static_cast<ifstream *>(inputStream.get())->is_open())
        {
            cerr << "Error opening file!" << endl;
            return;
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
            if (isWord && regex_search(currentPost, word) ||
                !isWord && regex_search(currentPost, topic))
                matchingPosts.push_back(printedPost);
        }
    }

    if (matchingPosts.empty())
        cout << "No posts found containing the " << (isWord ? "word" : "topic") << ": " << searchTerm << endl;
    else
    {
        cout << "Posts containing the " << (isWord ? "word" : "topic") << ": " << searchTerm << endl;
        for (const auto &post : matchingPosts)
            cout << post << endl;
    }
}
