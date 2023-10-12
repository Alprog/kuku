#pragma once

#include "types.h"
#include "cell.h"

class stack
{
public:
    stack();
    ~stack();

    void push(cell cell);
    void push_integer(integer integer);
    void push_byte(byte byte);
    void push_object(object_index object);

    cell* cells;
    cell* frame_start;
    cell* head;
};