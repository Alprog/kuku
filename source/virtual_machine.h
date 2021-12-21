#pragma once

#include "stack.h"
#include "cell.h"
#include "type_registry.h"
#include "data_type.h"
#include "instance.h"

class VirtualMachine
{
public:
    TypeRegistry TypeRegistry;
    Stack Stack;

    void test();

    void setLocal(int cellIndex, Cell cellValue);

    void setField(Instance instance, int cellIndex, Cell cellValue);
};