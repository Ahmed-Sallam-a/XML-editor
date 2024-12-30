#include "DrawGraph.h"

void generatePNG(const string& dotFilename, const string& pngFilename) {
    string command = "dot -Tpng " + dotFilename + " -o " + pngFilename;
    int result = system(command.c_str());
    if (result == 0) {
        cout << "Successfully generated " << pngFilename << endl;
    } else {
        cerr << "Failed to generate PNG file" << endl;
    }
}

int main() {
    Graph socialNetwork;
    string xmlContent = R"(
    <users>
<user>
<id>1</id>
<name>Ahmed Ali</name>
<posts>
<post>
<body> Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt. </body>
</post>
</posts>
<followers>
<follower><id>2</id></follower>
</followers>
</user>
<user>
<id>2</id>
<name>Yasser Ahmed</name>
<posts>
<post>
<body> Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore. </body>
</post>
</posts>
<followers>
<follower><id>1</id></follower>
</followers>
</user>
</users>
    )";

    parseXMLAndBuildGraph(xmlContent, socialNetwork);

    // Generate DOT file
    socialNetwork.generateDOTFile("social_network.dot");

    // Convert DOT to PNG
    generatePNG("social_network.dot", "social_network.png");

    return 0;
}
