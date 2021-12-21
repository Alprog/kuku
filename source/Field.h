#pragma once

#include <string>
#include "data_type.h"

class Class;

class Field
{
public:
    Field(Class& ownerClass, std::string name, DataType type, int instanceOffset);

    Class& OwnerClass;
    DataType Type;
    std::string Name;
    int InstanceOffset;
};