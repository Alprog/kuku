#pragma once

#include "types.h"
#include "cell.h"

class stack
{
public:
    stack();
    ~stack();

    void push(cell cell);

    cell* cells;
    cell* frame_start;
    cell* head;
};