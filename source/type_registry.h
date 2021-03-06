#pragma once

#include <vector>
#include "class.h"

class Type_registry
{
public:
    Class& register_class(std::string name);

    std::vector<Class> Classes;
};