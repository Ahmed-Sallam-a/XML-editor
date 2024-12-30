#include "XmlToJsonConverter.h"
#include <iostream>

int main() {
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