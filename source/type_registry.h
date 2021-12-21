#pragma once

#include <vector>
#include "class.h"

class TypeRegistry
{
public:
    Class& RegisterClass(std::string name);

    std::vector<Class> Classes;
};