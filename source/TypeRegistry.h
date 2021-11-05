#pragma once

#include <vector>
#include "Class.h"

class TypeRegistry
{
public:
    Class& RegisterClass(std::string name);

    std::vector<Class> Classes;
};