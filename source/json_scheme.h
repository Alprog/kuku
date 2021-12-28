#pragma once

#include "json_field.h"
#include <vector>

class Json_scheme
{
public:
    Json_scheme(std::vector<Base_json_field*> fields)
        : fields{ fields }
    {
    }

    std::vector<Base_json_field*> fields;
};