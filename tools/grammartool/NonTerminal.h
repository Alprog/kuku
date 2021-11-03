#pragma once

#include "Symbol.h"
#include "Production.h"

struct NonTerminal : Symbol
{    
    std::vector<Production> Productions;

    NonTerminal(std::string name)
        : Symbol{name}
    {
    }

    bool IsTerminal() override { return false; }
};