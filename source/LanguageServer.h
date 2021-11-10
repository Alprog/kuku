#pragma once

#include <string>
#include "json.h"
#include "IDEConnection.h"

class language_server
{
public:
    language_server();

private:
    void processMessage(nlohmann::json& message);
    void onInitialize(nlohmann::json& message);

    IDEConnection ideConnection;
};