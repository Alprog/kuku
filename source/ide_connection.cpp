
#include "ide_connection.h"
#include <iostream>
#include <string>

IDEConnection& operator>>(IDEConnection& ide, nlohmann::json& message)
{
    std::string line;

    getline(std::cin, line);
    auto index = line.find(':');
    auto count = std::atoi(line.substr(index + 1).c_str());

    getline(std::cin, line);

    std::string contentText;
    contentText.resize(count, 'x');
    std::cin.read(&contentText[0], count);

    message = nlohmann::json::parse(contentText);

    return ide;
}

IDEConnection& operator<<(IDEConnection& ide, nlohmann::json& message)
{
    auto contentText = message.dump();

    const auto contentLength = contentText.size();
    constexpr auto contentType = "utf-8";

    static std::string lineEnding = "\n";

    // header
    std::cout << "Content-Length: " << std::to_string(contentLength) << lineEnding;
    std::cout << "Content-Type: " << contentType << lineEnding;

    std::cout << lineEnding; // separator

    // content
    std::cout << contentText;

    std::cout.flush();

    return ide;
}