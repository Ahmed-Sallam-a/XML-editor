//
// Created by ahmed on 12/30/2024.
//
// Main function to handle command-line operations
#include "xml_lib.h"
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
        prettifyXML(inputFile, outputFile);
    }
    else if (command == "json")
    {
        // Placeholder for JSON conversion functionality
        cout << "JSON conversion functionality is not implemented yet." << endl;
    }
    else if (command == "mini")
    {
        // Implement minify functionality
        prettifyXML(inputFile, outputFile);
    }
    else if (command == "compress")
    {
        // Placeholder for compress functionality
        cout << "Compress functionality is not implemented yet." << endl;
    }
    else if (command == "decompress")
    {
        // Placeholder for decompress functionality
        cout << "Decompress functionality is not implemented yet." << endl;
    }
    else if (command == "draw")
    {
        // Placeholder for draw functionality
        cout << "Draw functionality is not implemented yet." << endl;
    }
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
        // Placeholder for most_influencer functionality
        cout << "Most Influencer functionality is not implemented yet." << endl;
    }
    else if (command == "mutual")
    {
        // Placeholder for mutual functionality
        cout << "Mutual functionality is not implemented yet." << endl;
    }
    else if (command == "suggest")
    {
        // Placeholder for suggest functionality
        cout << "Suggest functionality is not implemented yet." << endl;
    }
    else
    {
        cerr << "Unknown command: " << command << endl;
        return 1;
    }

    return 0;
}