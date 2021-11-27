#pragma once

union Cell;

struct Instance
{
public:
    void dump();

    Cell* Cells;
};