
#include "stack.h"

stack::stack()
{
    cells = new cell[1024 * 1024 / sizeof(cell)]; // 1 MB
    head = &cells[0];
    frame_start = &cells[0];
}

stack::~stack()
{
    if (cells != nullptr)
    {
        delete[] cells;
    }
}

void stack::push(cell cell)
{
    *head++ = cell;
}

void stack::push_integer(integer integer)
{
    (head++)->integer = integer;
}

void stack::push_byte(byte byte)
{
    (head++)->byte = byte;
}

void stack::push_object(object_index object)
{
    (head++)->object = object;
}