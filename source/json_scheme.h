#pragma once

#include "json_field.h"
#include <vector>

class JsonScheme
{
public:
    JsonScheme(std::vector<BaseJsonField*> fields)
        : fields{ fields }
    {
    }

    std::vector<BaseJsonField*> fields;
};