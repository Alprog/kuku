
#include "LanguageServer.h"

#include <iostream>
#include <fstream>
#include "primitives.h"
#include "LSPEnums.h"

language_server::language_server()
{
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
    else if (method == "initialized")
        {} // nothing to do
    else if (method == "textDocument/didOpen")
        onDidOpen(message);
    else if (method == "textDocument/didChange")
        onDidChange(message);
    else if (method == "textDocument/completion")
        onCompletion(message);
    else if (method == "$/cancelRequest")
        {} // nothing to do
    else
        throw new std::exception("unknown method");
}

void language_server::onInitialize(nlohmann::json& message)
{
    auto name = message["params"]["clientInfo"]["name"].get<std::string>();

    auto id = message["id"].get<int>();

    nlohmann::json result = {
        { "capabilities", {
            { "textDocumentSync", TextDocumentSyncKind::Incremental },
            { "completionProvider", {
                { "resolveProvider", true }
            }},
            { "workspace", {
                { "workspaceFolders", {
                    { "supported", true }
                }}
            }}
        }}
    };

    nlohmann::json response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ideConnection << response;
}

void language_server::onDidOpen(nlohmann::json& message)
{
    /*
        "textDocument": {
            "uri": "file:///c%3A/Users/alpro/Desktop/2.txt",
            "version": 3
        },
        "contentChanges": [
            {
                "range": {
                    "start": {
                        "line": 5,
                        "character": 0
                    },
                    "end": {
                        "line": 5,
                        "character": 0
                    }
                },
                "rangeLength": 0,
                "text": "A"
            }
    ]*/
}

void language_server::onDidChange(nlohmann::json& message)
{
    /*
        "textDocument": {
            "uri": "file:///c%3A/Users/alpro/Desktop/2.txt"
        },
        "position": {
            "line": 5,
            "character": 1
        },
        "context": {
            "triggerKind": 1
        }
    */
}

void language_server::onCompletion(nlohmann::json& message)
{
     /*
        "textDocument": {
            "uri": "file:///c%3A/Users/alpro/Desktop/2.txt",
            "version": 4
        },
        "contentChanges": [
            {
                "range": {
                    "start": {
                        "line": 5,
                        "character": 1
                    },
                    "end": {
                        "line": 5,
                        "character": 1
                    }
                },
                "rangeLength": 0,
                "text": "A"
            }
        ]
    */
}