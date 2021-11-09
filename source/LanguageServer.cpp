
#include "LanguageServer.h"

#include <iostream>
#include <fstream>
#include "primitives.h"

language_server::language_server()
{
    std::ofstream ofile;
    ofile.open("C:/KuKu/source/x64/Debug/out.txt");

    std::string message;
    while (true)
    { 
        getline(std::cin, message);
        auto index = message.find(':');
        auto count = std::atoi(message.substr(index + 1).c_str());
        
        getline(std::cin, message);
        
        message.resize(count, 'x');
        std::cin.read(&message[0], count);

        processMessage(message);           
    }
}

void language_server::processMessage(std::string message)
{
    auto json = nlohmann::json::parse(message);
    auto method = json["method"].get<std::string>();

    if (method == "initialize")
        onInitialize(json);
    else
        throw new std::exception("unknown method");
}

void language_server::onInitialize(nlohmann::json json)
{
    auto name = json["params"]["clientInfo"]["name"].get<std::string>();

    auto id = json["id"].get<int>();
    auto content = R"({"jsonrpc": "2.0", "id": )" + std::to_string(id) + R"(, "result": null })";

    auto count = content.size();
    
    std::string header = "Content-Length: " + std::to_string(count) + "\n\n";

    std::string fullMessage = header + content;

    std::cout << fullMessage;
}