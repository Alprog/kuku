#pragma once

#include "types.h"
#include "cell.h"

class stack
{
public:
    stack();
    ~stack();

    void push(Cell cell);

    Cell* cells;
    Cell* frame_start;
    Cell* head;
};