#pragma once

#include <string>
#include <vector>
#include "function.h"
#include "data_type.h"
#include "field.h"
#include "cell.h"

class Class
{
public:
    Class(std::string name);

    std::string Name;

    Field& registerField(std::string name, DataType dataType);
    Instance createInstance();

    void dump(Instance instance);

    int InstanceSize;

    std::vector<Field> Fields;
    std::vector<Function> Functions;
};