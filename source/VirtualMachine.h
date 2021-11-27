#pragma once

#include "Stack.h"
#include "Cell.h"
#include "TypeRegistry.h"
#include "DataType.h"
#include "Instance.h"

class VirtualMachine
{
public:
    TypeRegistry TypeRegistry;
    Stack Stack;

    void test();

    void setLocal(int cellIndex, Cell cellValue);

    void setField(Instance instance, int cellIndex, Cell cellValue);
};