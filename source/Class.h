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

    std::string name;

    field& register_field(std::string name, data_type data_type);
    Instance create_instance();

    void dump(Instance instance);

    int instance_size;

    std::vector<field> fields;
    std::vector<Function> functions;
};