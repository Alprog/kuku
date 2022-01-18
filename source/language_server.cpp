
#include "language_server.h"

#include <iostream>
#include <fstream>
#include "types.h"
#include "lsp/enums.h"
#include "lsp/text_document_item.h"
#include "unicode.h"
#include "lsp/did_change_text_document_params.h"

language_server::language_server()
{
	while (true)
	{
		json::object message;
		ide_connection >> message;
		process_message(message);
	}
}

void language_server::process_message(json::object& message)
{
    auto method = message["method"].get<std::string>();

    if (method == "initialize")
        on_initialize(message);
    else if (method == "initialized")
        {} // nothing to do
    else if (method == "textDocument/didOpen")
        on_did_open(message);
    else if (method == "textDocument/didChange")
        on_did_change(message);
    else if (method == "textDocument/hover")
        on_hover(message);
    else if (method == "textDocument/completion")
        on_completion(message);
    else if (method == "$/cancelRequest")
        {} // nothing to do
    else
        throw new std::exception("unknown method");
}

void language_server::on_initialize(json::object& message)
{
    auto name = message["params"]["clientInfo"]["name"].get<std::string>();

    auto id = message["id"].get<int>();

    json::object result = {
        { "capabilities", {
            { "textDocumentSync", lsp::text_document_sync_kind::Incremental },
            { "completionProvider", {
                { "resolveProvider", true }
            }},
            { "workspace", {
                { "workspaceFolders", {
                    { "supported", true }
                }}
            }},
            { "hoverProvider", true }
        }}
    };

    json::object response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ide_connection << response;
}

void language_server::on_did_open(json::object& message)
{
    auto json = message["params"]["textDocument"];
    auto document = from_json<lsp::text_document_item>(json);

    source_project.add_file(document.uri, document.text);
    source_project.process_all();
}

void language_server::on_did_change(json::object& message)
{
    auto params = from_json<lsp::did_change_text_document_params>(message["params"]);
    auto uri = params.text_document.uri;
    auto module = source_project.get_module(uri);
    if (module != nullptr)
    {
        for (auto& change : params.content_changes)
        {
            module->document.change_content(change);
        }
        module->tokens.clear();
        module->tokenize();
    }
}

void language_server::on_hover(json::object& message)
{
    auto id = message["id"].get<int>();
    auto uri = message["params"]["textDocument"]["uri"].get<std::string>();
   
    
    auto line = message["params"]["position"]["line"].get<int>();
    auto character = message["params"]["position"]["character"].get<int>();
    auto position = lsp::position(line, character);

    json::object result = nullptr;

    auto module = source_project.get_module(uri);
    if (module != nullptr)
    {
        Token* token = module->get_token(position);
        if (token != nullptr)
        {
            result = {
                { "contents", token->get_hover_text() }
            };
        }
    }

    json::object response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ide_connection << response;
}

void language_server::on_completion(json::object& message)
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