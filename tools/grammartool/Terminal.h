#pragma once

#include "Symbol.h"
#include <string>

struct Terminal : Symbol
{
    Terminal(std::string name)
        : Symbol{ name }
    {
    }

    bool IsTerminal() override { return true; }
};