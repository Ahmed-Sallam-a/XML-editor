#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream> // For file handling



using namespace std;
//can be used to read the file but it is compensated by Gui   \/ \/ \/


// string parseXMLToString(const string& filePath) {    
//     ifstream xmlFile(filePath);
//     if (!xmlFile.is_open()) {
//         cerr << "Error: Unable to open the file: " << filePath << endl;
//         return "";
//     }
//     string line, content, result;
//     while (getline(xmlFile, line)) {
//         content += line; // Read the file line by line into a single string
//     }
//     xmlFile.close();
//     return content;
// }

string compress( string input) {
   
  // string input = parseXMLToString(filePath);
  //compensated by Gui
    unordered_map<string, int> stringTable;
    int code = 256; // Start with the first available code after ASCII  ahm 7aga fe algo

    for (int i = 0; i < 256; i++) {
        stringTable[string(1, char(i))] = i; 
    }

    string P = "";
    P += input[0]; // First input character da elmafrood sallaaaaaam ydeh as a string
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

    string compressedString;
    for (int code : outputCodes) {
        compressedString += to_string(code) ;
    }
    return compressedString;
    // Write the compressed data to a .comp file       //compensated by Gui
    // ofstream compFile("C:\\Users\\AHMED SAMIR\\Desktop\\DSA\\tut5\\tut5problems\\tst1.comp", ios::binary);
    // if (compFile.is_open()) {
    //     for (int code : outputCodes) {
    //         compFile.write(reinterpret_cast<const char*>(&code), sizeof(code));
    //     }
    //     compFile.close();///garbage
    //     cout << "Compressed data written to output.comp\n";
    // } else {
    //     cerr << "Error: Unable to open the .comp file for writing.\n";
    // }
}
string decompress(string input) {//hyd5l string w yrg3 string
    // ifstream compFile(inputFilePath, ios::binary);//compensated by Gui
    // if (!compFile.is_open()) {
    //     cerr << "Error: Unable to open the .comp file for reading: " << inputFilePath << endl;
    //     return;
    // }

    // Read the compressed data into a vector of integers
    // int code;
    // while (compFile.read(reinterpret_cast<char*>(&code), sizeof(code))) {
    //     compressedCodes.push_back(code);
    // }
    // compFile.close();

    vector<int> compressedCodes;//momkn hna fe mo4kla spaces ya sallaaaam 
    for (char ch : input) {
        compressedCodes.push_back(static_cast<int>(ch));
    }
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
            cerr << "Error: Invalid code encountered during decompression.\n";//momkn hna fe mo4kla spaces ya sallaaaam htsm3 hna
            return;
        }

        decompressed += current;

        // Add new entry to the table
        stringTable[tableIndex++] = previous + current[0];
        previous = current;
    }
    return decompressed;
    //can be used to put data into  the file but it is compensated by Gui   \/ \/ \/
    // Write the decompressed data to an XML file
    // ofstream xmlFile(outputFilePath);
    // if (xmlFile.is_open()) {
    //     xmlFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    //     xmlFile << "<decompressedData>\n";
    //     xmlFile << "  <content>" << decompressed << "</content>\n";
    //     xmlFile << "</decompressedData>\n";
    //     xmlFile.close();
    //     cout << "Decompressed data written to " << outputFilePath << endl;
    // } else {
    //     cerr << "Error: Unable to open the XML file for writing: " << outputFilePath << endl;
    // }
}


