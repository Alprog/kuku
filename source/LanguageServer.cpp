
#include "LanguageServer.h"

#include <iostream>
#include <fstream>
#include "primitives.h"

language_server::language_server()
{
    std::ofstream ofile;
    ofile.open("C:/KuKu/source/x64/Debug/out.txt");

    while (true)
    { 
        nlohmann::json message;
        ideConnection >> message;
        processMessage(message);           
    }
}

void language_server::processMessage(nlohmann::json& message)
{
    auto method = message["method"].get<std::string>();

    if (method == "initialize")
        onInitialize(message);
    else
        throw new std::exception("unknown method");
}

void language_server::onInitialize(nlohmann::json& message)
{
    auto name = message["params"]["clientInfo"]["name"].get<std::string>();

    auto id = message["id"].get<int>();

    nlohmann::json response;
    response["jsonrpc"] = "2.0";
    response["id"] = id;
    response["result"] = nlohmann::json::parse(R"(
        {
            "capabilities": 
            {
                "textDocumentSync": 2,
                "completionProvider":
                {
                    "resolveProvider": true
                },
                "workspace": 
                {
                    "workspaceFolders": 
                    {
                        "supported": true
                    }
                }
            }
        }
    )");


    ideConnection << response;
}