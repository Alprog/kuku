#pragma once

#include "primitives.h"

class Stack
{
public:
    Stack()
    {
        Memory = new byte[1024 * 1024]; // 1 MB
        Pointer = nullptr;
    }

    byte* Memory;
    byte* Pointer;
};