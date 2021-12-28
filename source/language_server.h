#pragma once

#include <string>
#include "json.h"
#include "ide_connection.h"

class Language_server
{
public:
    Language_server();

private:
    void process_message(nlohmann::json& message);
    void on_initialize(nlohmann::json& message);
    void on_did_open(nlohmann::json& message);
    void on_did_change(nlohmann::json& message);
    void on_completion(nlohmann::json& message);

    Ide_connection ide_connection;
};