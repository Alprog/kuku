#pragma once

#include <string>
#include "json/object.h"
#include "ide_connection.h"
#include "source_project.h"

class Language_server
{
public:
    Language_server();

private:
    void process_message(json::object& message);
    void on_initialize(json::object& message);
    void on_did_open(json::object& message);
    void on_did_change(json::object& message);
    void on_hover(json::object& message);
    void on_completion(json::object& message);
    
    Source_project source_project;
    Ide_connection ide_connection;
};