#pragma once

#include <vector>
#include "class.h"

class type_registry
{
public:
    user_class& register_class(std::string name);

    std::vector<user_class> classes;
};