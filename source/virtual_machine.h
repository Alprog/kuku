#pragma once

#include "stack.h"
#include "cell.h"
#include "type_registry.h"
#include "data_type.h"
#include "instance.h"

class Virtual_machine
{
public:
    TypeRegistry TypeRegistry;
    Stack Stack;

    void test();

    void setLocal(int cellIndex, Cell cellValue);

    void setField(Instance instance, int cellIndex, Cell cellValue);
};