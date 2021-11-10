#pragma once

#include <string>
#include "json.h"

class IDEConnection
{
public:
    friend IDEConnection& operator<<(IDEConnection& ide, nlohmann::json& message);
    friend IDEConnection& operator>>(IDEConnection& ide, nlohmann::json& message);
};