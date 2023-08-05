#pragma once

union cell;

struct Instance
{
public:
    void dump();

    cell* cells;
};