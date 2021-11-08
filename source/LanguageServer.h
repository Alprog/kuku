#pragma once

#include <string>
#include "json.h"

class language_server
{
public:
    language_server();

private:
    void processMessage(std::string message);
    void onInitialize(nlohmann::json json);
};