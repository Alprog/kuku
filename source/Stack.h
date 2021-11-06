#pragma once

#include "primitives.h"
#include "Cell.h"

class Stack
{
public:
    Stack()
    {
        Cells = new Cell[1024 * 1024 / sizeof(Cell)]; // 1 MB
        Pointer = nullptr;
    }

    Cell* Cells;
    Cell* Pointer;
};