//
// Created by ahmed on 12/30/2024.
//

#ifndef XMLTOJSONCONVERTER_H
#define XMLTOJSONCONVERTER_H

#include <string>
#include <vector>
#include <map>

class XmlToJsonConverter {
private:
    struct Node {
        std::string name;                                   // Tag name
        std::string value;                                  // Content inside the tag
        std::map<std::string, std::string> attributes;      // Tag attributes
        std::vector<Node> children;                         // Child nodes
    };

    // Trim leading and trailing whitespace
    static std::string trim(const std::string& str);

    // Parse XML string into a tree structure
    static Node parseXml(const std::string& xml);

    // Convert Node to JSON
    static std::string nodeToJson(const Node& node, int indent = 0);

public:
    // Convert XML string to JSON string
    static std::string convert(const std::string& xml);
};

#endif // XMLTOJSONCONVERTER_H#
