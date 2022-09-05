#pragma once

#include "types.h"
#include "cell.h"

class Stack
{
public:
    Stack()
    {
        cells = new Cell[1024 * 1024 / sizeof(Cell)]; // 1 MB
        pointer = nullptr;
    }

    ~Stack()
    {
        if (cells != nullptr)
        {
            delete[] cells;
        }
    }

    Cell* cells;
    Cell* pointer;
};