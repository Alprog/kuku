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

    void test()
    {
        auto vectorClass = TypeRegistry.RegisterClass("Vector");
        vectorClass.RegisterField("X", DataType::Number);
        vectorClass.RegisterField("Y", DataType::Number);
        vectorClass.RegisterField("Z", DataType::Number);

        auto vectorInstance = vectorClass.CreateInstance();

        Cell cell;
        cell.number = 41;

        SetField(vectorInstance, 2, cell);
        vectorInstance.Dump();
    }

    void SetLocal(int cellIndex, Cell cellValue)
    {
        Stack.Cells[cellIndex] = cellValue;
    }

    void SetField(Instance instance, int cellIndex, Cell cellValue)
    {
        instance.Cells[cellIndex] = cellValue;
    }
};