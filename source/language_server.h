#pragma once

#include <string>
#include "json.h"
#include "ide_connection.h"

class language_server
{
public:
    language_server();

private:
    void processMessage(nlohmann::json& message);
    void onInitialize(nlohmann::json& message);
    void onDidOpen(nlohmann::json& message);
    void onDidChange(nlohmann::json& message);
    void onCompletion(nlohmann::json& message);

    IDEConnection ideConnection;
};