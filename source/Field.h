#pragma once

#include <string>
#include "data_type.h"

class Class;

class Field
{
public:
    Field(Class& owner_class, std::string name, Data_type type, int instance_offset);

    Class& owner_class;
    Data_type type;
    std::string name;
    int instance_offset;
};