#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream> // For file handling

//#include <regex> // For regex_replace

using namespace std;

string parseXMLToString(const string& filePath) {
    ifstream xmlFile(filePath);
    if (!xmlFile.is_open()) {
        cerr << "Error: Unable to open the file: " << filePath << endl;
        return "";
    }

    string line, content, result;
    while (getline(xmlFile, line)) {
        content += line; // Read the file line by line into a single string
    }
    xmlFile.close();

    // // Use a regex to remove all XML tags
    // regex tagRegex("<[^>]+>");
    // result = regex_replace(content, tagRegex, "");

    // // Trim any leading or trailing whitespace
    // result.erase(0, result.find_first_not_of(" \t\n\r"));
    // result.erase(result.find_last_not_of(" \t\n\r") + 1);

    return content;
}

void compress(const string& filePath, const string& outputFilePath) {
    string input = parseXMLToString(filePath);
    unordered_map<string, int> stringTable;
    int code = 256; // Start with the first available code after ASCII

    for (int i = 0; i < 256; i++) {
        stringTable[string(1, char(i))] = i; // Add single characters
    }

    string P = "";
    P += input[0]; // First input character
    vector<int> outputCodes;

    for (size_t i = 1; i < input.length(); i++) {
        char C = input[i]; // Next input character
        if (stringTable.find(P + C) != stringTable.end()) {
            P = P + C; // P + C is in the table
        } else {
            outputCodes.push_back(stringTable[P]); // Output the code for P
            stringTable[P + C] = code++; // Add P + C to the table
            P = C; // Set P to C
        }
    }

    // Output the code for the last P
    outputCodes.push_back(stringTable[P]);

    // Write the compressed data to a .comp file
    ofstream compFile(outputFilePath, ios::binary);
    if (compFile.is_open()) {
        for (int code : outputCodes) {
            compFile.write(reinterpret_cast<const char*>(&code), sizeof(code));
        }
        compFile.close();
        cout << "Compressed data written to output.comp\n";
    } else {
        cerr << "Error: Unable to open the .comp file for writing.\n";
    }
}
void decompress(const string& inputFilePath, const string& outputFilePath) {
    ifstream compFile(inputFilePath, ios::binary);
    if (!compFile.is_open()) {
        cerr << "Error: Unable to open the .comp file for reading: " << inputFilePath << endl;
        return;
    }

    // Read the compressed data into a vector of integers
    vector<int> compressedCodes;
    int code;
    while (compFile.read(reinterpret_cast<char*>(&code), sizeof(code))) {
        compressedCodes.push_back(code);
    }
    compFile.close();

    // Initialize the string table with single character strings
    unordered_map<int, string> stringTable;
    for (int i = 0; i < 256; i++) {
        stringTable[i] = string(1, char(i)); // Add single characters
    }

    // Decompression logic
    int tableIndex = 256; // Next available code index
    string previous = stringTable[compressedCodes[0]]; // First code
    string decompressed = previous;

    for (size_t i = 1; i < compressedCodes.size(); i++) {
        string current;
        if (stringTable.find(compressedCodes[i]) != stringTable.end()) {
            current = stringTable[compressedCodes[i]];
        } else if (compressedCodes[i] == tableIndex) {
            current = previous + previous[0]; // Special case for new entries
        } else {
            cerr << "Error: Invalid code encountered during decompression.\n";
            return;
        }

        decompressed += current;

        // Add new entry to the table
        stringTable[tableIndex++] = previous + current[0];
        previous = current;
    }

    // Write the decompressed data to an XML file
    ofstream xmlFile(outputFilePath);
    if (xmlFile.is_open()) {
       // xmlFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        xmlFile << "<decompressedData>\n";
        xmlFile << "  <content>" << decompressed << "</content>\n";
        xmlFile << "</decompressedData>\n";
        xmlFile.close();
        cout << "Decompressed data written to " << outputFilePath << endl;
    } else {
        cerr << "Error: Unable to open the XML file for writing: " << outputFilePath << endl;
    }
}

int main(int argc, char* argv[]) {
     // Ensure at least 6 arguments are provided
    if (argc != 6) {
        cerr << "Usage: xml_editor compress/decompress -i input_file.xml -o output_file.xml" << endl;
        return 1;
    }
    // Check the command and arguments
    string command = argv[1];
    string inputFlag = argv[2];
    string inputFile = argv[3];
    string outputFlag = argv[4];
    string outputFile = argv[5];
    if ((command != "compress"&&command != "decompress") || inputFlag != "-i" || outputFlag != "-o") {
        cerr << "Invalid command or flags. Usage: xml_editor format -i input_file.xml -o output_file.xml" << endl;
        return 1;
    }
    
    if(command=="compress"){compress(inputFile,outputFile);}
    else if(command=="decompress"){decompress(inputFile,outputFile);}

    // compress(input);
    //    string outputFilePath = "C:\\Users\\AHMED SAMIR\\Desktop\\DSA\\tut5\\tut5problems\\kerowahmed.xml";
    //  decompress("C:\\Users\\AHMED SAMIR\\Desktop\\DSA\\tut5\\tut5problems\\tst1.comp", outputFilePath);

    return 0;
}