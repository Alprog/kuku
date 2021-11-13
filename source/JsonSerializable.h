#pragma once

#include "json.h"

class JsonScheme;

class JsonSerializable
{
public:
    nlohmann::json toJson();

    virtual JsonScheme& GetJsonScheme() = 0;
};