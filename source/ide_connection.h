#pragma once

#include <string>
#include "json.h"

class Ide_connection
{
public:
    friend Ide_connection& operator<<(Ide_connection& ide, nlohmann::json& message);
    friend Ide_connection& operator>>(Ide_connection& ide, nlohmann::json& message);
};