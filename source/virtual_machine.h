#pragma once

#include "stack.h"
#include "cell.h"
#include "type_registry.h"
#include "data_type.h"
#include "instance.h"
#include "object_header.h"

class virtual_machine
{
public:
    std::vector<object_header> headers;

    type_registry type_registry;
    stack stack;

    void test();

    void set_local(int cell_index, cell cell_value);

    void set_field(instance instance, int cell_index, cell cell_value);
};