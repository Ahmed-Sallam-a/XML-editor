#include "XmlToJsonConverter.h"
#include <iostream>

int main1() {
    std::string xmlInput = R"( <configuration>
<appender name="console" class="ch.qos.logback.core.ConsoleAppender">
<encoder>
<pattern>%d{yyyy-MM-dd HH:mm:ss} - %msg%n</pattern>
</encoder>
</appender>
<appender name="FILE" class="ch.qos.logback.core.rolling.RollingFileAppender">
<file>logs/app.log</file>
<encoder>
<pattern>%d{yyyy-MM-dd HH:mm:ss} - %msg%n</pattern>
</encoder>
</appender>
</configuration> )";

    std::string jsonOutput = XmlToJsonConverter::convert(xmlInput);
    std::cout << jsonOutput << std::endl;

    return 0;
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_file output_file\n";
        return 1;
    }
    std::string inputPath = argv[1];
    std::string outputPath = argv[2];
    if (XmlToJsonConverter::processFiles(inputPath, outputPath)) {
        std::cout << "Conversion successful.\n";
        return 0;
    } else {
        std::cerr << "Conversion failed.\n";
        return 1;
    }
}