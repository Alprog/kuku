#pragma once

#include <string>
#include <vector>
#include "rt/function.h"
#include "data_type.h"
#include "field.h"
#include "instance.h"

namespace rt
{
    class user_class
    {
    public:
        user_class(std::string name);

        std::string name;

        field& register_field(std::string name, data_type data_type);
        instance create_instance();

        void dump(instance instance);

        int instance_size;

        std::vector<field> fields;
        std::vector<function> vtable;
    };
}