
#include "stack.h"

stack::stack()
{
    cells = new Cell[1024 * 1024 / sizeof(Cell)]; // 1 MB
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

void stack::push(Cell cell)
{
    *head++ = cell;
}