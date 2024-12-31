//
// Created by ahmed on 12/30/2024.
//
// Main function to handle command-line operations
#include "xml_lib.h"
#include "xmltojsonconverter.h"
#include "DrawGraph.h"

using namespace std;
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
    int suggestedId;
    vector<int> ids;

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

        else if (arg == "-ids")
        {
            ids = parseStringToVector(argv[i + 1]);
        }

        else if (arg == "-id") // -id 1
            suggestedId = stoi(getReqArg(i, argc, argv, "-id"));

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
        checkXMLConsistencyCMD(inputFile, outputFile, fixErrors);

    else if (command == "format")
        prettifyXML(inputFile, outputFile);

    else if (command == "json")
    {
        if (XmlToJsonConverter::processFiles(inputFile, outputFile))
        {
            cout << "Conversion successful.\n";
            return 0;
        }
        else
        {
            std::cerr << "Conversion failed.\n";
            return 1;
        }
    }
    else if (command == "mini")
        minifyXMLFile(inputFile, outputFile);

    else if (command == "compress")
    {
        cout << "Compress functionality is not implemented yet." << endl;
    }
    else if (command == "decompress")
    {
        cout << "Decompress functionality is not implemented yet." << endl;
    }
    else if (command == "draw")
        processXMLToPNG(inputFile, outputFile);

    else if (command == "most_active")
    {
        readXML(inputFile);
        pair<int, string> mostActive = getMostActiveUser();
        if (mostActive.first != -1)
            cout << "Most Active User: ID=" << mostActive.first << ", Name=" << mostActive.second << endl;
        else
            cout << "No active users found." << endl;
    }
    else if (command == "most_influencer")
    {
        cout << "Most Influencer functionality is not implemented yet." << endl;
    }
    else if (command == "mutual")
    {
        readXML(inputFile);
        vector<int> mutualFollowers = getMutualFollowers(ids);
        if (mutualFollowers.size() != 0)
        {
            cout << "Mutual friends are: ";
            for (int i = 0; i < mutualFollowers.size(); i++)
                cout << mutualFollowers[i] << " ";
            cout << endl;
        }
        else
            cout << "No mutual followers found" << endl;
    }
    else if (command == "suggest")
    {
        readXML(inputFile);
        vector<int> suggestions = suggestUsersToFollow(suggestedId);
        if (suggestions.size() != 0)
        {
            cout << "Suggested users are: ";
            for (int i = 0; i < suggestions.size(); i++)
                cout << suggestions[i] << " ";
            cout << endl;
        }
        else
            cout << "No suggestions found" << endl;
    }
    else
    {
        cerr << "Unknown command: " << command << endl;
        return 1;
    }

    return 0;
}
