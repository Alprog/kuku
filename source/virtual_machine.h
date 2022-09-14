#pragma once

#include "stack.h"
#include "cell.h"
#include "type_registry.h"
#include "data_type.h"
#include "instance.h"

class Virtual_machine
{
public:
    Type_registry Type_registry;
    stack stack;

    void test();

    void set_local(int cell_index, Cell cell_value);

    void set_field(Instance instance, int cell_index, Cell cell_value);
};