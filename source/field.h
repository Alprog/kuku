#pragma once

#include <string>
#include "data_type.h"

class Class;

class field
{
public:
    field(Class& const owner_class, std::string name, data_type type, int instance_offset);

    Class& owner_class;
    data_type type;
    std::string name;
    int instance_offset;
};