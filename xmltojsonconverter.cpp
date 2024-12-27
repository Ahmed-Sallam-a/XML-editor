#include <string>
#include <map>
#include <vector>
#include <regex>
#include <stdexcept>

class XmlToJsonConverter {
private:
    struct Node {
        std::string name;                   // Tag name
        std::string value;                  // Content inside the tag
        std::map<std::string, std::string> attributes; // Tag attributes
        std::vector<Node> children;         // Child nodes
    };

    // Trim leading and trailing whitespace
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    // Parse XML string into a tree structure
    static Node parseXml(const std::string& xml) {
        std::regex tagRegex(R"(<(/?)(\w+)([^>]*)>)");
        std::smatch match;

        Node root;
        std::vector<Node*> stack; // Keeps track of the parent-child hierarchy
        size_t pos = 0;

        while (std::regex_search(xml.begin() + pos, xml.end(), match, tagRegex)) {
            std::string tag = match[2];           // Extract tag name
            std::string attrString = match[3];    // Attributes inside the tag
            bool isClosingTag = match[1] == "/";  // Check if it's a closing tag

            // Handle content between tags
            std::string content = trim(xml.substr(pos, match.position()));
            if (!stack.empty() && !content.empty()) {
                stack.back()->value += content;   // Add content to the current node
            }

            if (isClosingTag) {
                // Check if the closing tag matches the current node
                if (stack.empty() || stack.back()->name != tag) {
                    throw std::runtime_error("Malformed XML: unmatched closing tag </" + tag + ">");
                }
                stack.pop_back();  // Pop the current node from the stack
            } else {
                // Create a new node for the opening tag
                Node newNode;
                newNode.name = tag;

                // Parse attributes
                std::regex attrRegex("([\\w:-]+)\\s*=\\s*\"([^\"]*)\"");
                std::smatch attrMatch;
                while (std::regex_search(attrString, attrMatch, attrRegex)) {
                    newNode.attributes[attrMatch[1]] = attrMatch[2];
                    attrString = attrMatch.suffix();  // Move to the next attribute
                }

                if (!stack.empty()) {
                    // Add the new node as a child of the current node
                    stack.back()->children.push_back(newNode);
                    stack.push_back(&stack.back()->children.back());
                } else {
                    // This is the root node
                    if (!root.name.empty()) {
                        throw std::runtime_error("Malformed XML: multiple root elements.");
                    }
                    root = newNode;
                    stack.push_back(&root);
                }
            }

            pos += match.position() + match.length();  // Move to the next tag
        }

        // Handle remaining content after the last tag
        if (!stack.empty() && pos < xml.length()) {
            stack.back()->value += trim(xml.substr(pos));
        }

        if (!stack.empty()) {
            throw std::runtime_error("Malformed XML: unclosed tags remain.");
        }

        return root;
    }
    static std::string nodeToJson(const Node& node, int indent = 0) {
        std::ostringstream json;
        std::string indentation(indent, ' ');

        if (node.children.empty() && node.attributes.empty()) {
            // If the node is a simple leaf node without attributes, just output the value
            json << "\"" << node.value << "\"";
            return json.str();
        }

        json << "{\n";

        // Add attributes (if any)
        for (const auto& [key, value] : node.attributes) {
            json << indentation << "  \"@" << key << "\": \"" << value << "\",\n";
        }

        // Add value (if present) only when the node has attributes or children
        if (!node.value.empty() && !node.attributes.empty()) {
            json << indentation << R"(  "#text": ")" << node.value << "\",\n";
        }

        // Add children (if any)
        for (size_t i = 0; i < node.children.size(); ++i) {
            const Node& child = node.children[i];
            json << indentation << "  \"" << child.name << "\": " << nodeToJson(child, indent + 2);
            if (i < node.children.size() - 1) {
                json << ",";
            }
            json << "\n";
        }

        json << indentation << "}";
        return json.str();
    }


public:
    static std::string convert(const std::string& xml) {
        try {
            Node root = parseXml(xml);
            std::ostringstream json;
            json << "{\n  \"" << root.name << "\": " << nodeToJson(root, 2) << "\n}";
            return json.str();
        } catch (const std::exception& e) {
            return std::string("Error: ") + e.what();
        }
    }
};
