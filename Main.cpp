#include "DrawGraph.h"

int main1() {
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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input.xml> <output.png>" << endl;
        return 1;
    }

    string xmlFilename = argv[1];
    string pngFilename = argv[2];

    processXMLToPNG(xmlFilename, pngFilename);

    return 0;
}

