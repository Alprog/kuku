#pragma once

union Cell;

struct Instance
{
public:
    void Dump();

    Cell* Cells;
};