#pragma once

#include <string>
#include <vector>
#include "Function.h"
#include "DataType.h"
#include "Field.h"
#include "Cell.h"

class Class
{
public:
    Class(std::string name);

    std::string Name;

    Field& RegisterField(std::string name, DataType dataType);
    Instance CreateInstance();

    void Dump(Instance instance);

    int InstanceSize;

    std::vector<Field> Fields;
    std::vector<Function> Functions;
};