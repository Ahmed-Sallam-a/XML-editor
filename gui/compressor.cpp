// compressor.cpp
#include "compressor.h"

#include <unordered_map>
#include <vector>
#include <fstream>    // For file handling (if needed in future)
#include <algorithm>  // For std::replace
#include <iostream>   // For std::cerr (optional, can use qWarning instead in Qt)

namespace Compressor {

std::string compress(const std::string& input) {
    if (input.empty()) {
        return "";
    }

    std::unordered_map<std::string, int> stringTable;
    int code = 256; // Start with the first available code after ASCII

    // Initialize the string table with single character strings
    for (int i = 0; i < 256; ++i) {
        stringTable[std::string(1, static_cast<char>(i))] = i;
    }

    std::string P;
    P += input[0]; // Initialize P with the first character
    std::vector<int> outputCodes;

    for (size_t i = 1; i < input.length(); ++i) {
        char C = input[i];
        std::string PC = P + C;

        if (stringTable.find(PC) != stringTable.end()) {
            P = PC;
        } else {
            outputCodes.push_back(stringTable[P]);
            stringTable[PC] = code++;
            P = std::string(1, C);
        }
    }

    // Output the code for the last P
    outputCodes.push_back(stringTable[P]);

    // Concatenate the codes into a single string
    std::string compressedString;
    for (int code : outputCodes) {
        compressedString += std::to_string(code);
        // Optionally, add a delimiter if needed for proper parsing
        compressedString += " "; // Delimiter (space) between codes
    }

    return compressedString;
}

std::string decompress(const std::string& input) {
    if (input.empty()) {
        return "";
    }

    // Split the input string into individual codes
    std::vector<int> compressedCodes;
    size_t pos = 0;
    size_t len = input.length();

    while (pos < len) {
        size_t nextSpace = input.find(' ', pos);
        if (nextSpace == std::string::npos) {
            nextSpace = len;
        }

        std::string codeStr = input.substr(pos, nextSpace - pos);
        if (!codeStr.empty()) {
            try {
                int code = std::stoi(codeStr);
                compressedCodes.push_back(code);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid code encountered during decompression: " << codeStr << std::endl;
                // Optionally, handle the error more gracefully or skip the invalid code
            }
        }

        pos = nextSpace + 1;
    }

    if (compressedCodes.empty()) {
        return "";
    }

    std::unordered_map<int, std::string> stringTable;
    for (int i = 0; i < 256; ++i) {
        stringTable[i] = std::string(1, static_cast<char>(i));
    }

    int tableIndex = 256; // Next available code index
    int firstCode = compressedCodes[0];
    if (stringTable.find(firstCode) == stringTable.end()) {
        std::cerr << "Invalid initial code during decompression: " << firstCode << std::endl;
        return "";
    }

    std::string previous = stringTable[firstCode];
    std::string decompressed = previous;

    for (size_t i = 1; i < compressedCodes.size(); ++i) {
        int currentCode = compressedCodes[i];
        std::string current;

        if (stringTable.find(currentCode) != stringTable.end()) {
            current = stringTable[currentCode];
        } else if (currentCode == tableIndex) {
            current = previous + previous[0];
        } else {
            std::cerr << "Invalid code encountered during decompression: " << currentCode << std::endl;
            return "";
        }

        decompressed += current;
        stringTable[tableIndex++] = previous + current[0];
        previous = current;
    }

    return decompressed;
}

} // namespace Compressor
