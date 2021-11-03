#pragma once

struct Symbol
{
    std::string Name;

    Symbol(std::string name)
        : Name {name}
    {
    }

    virtual bool IsTerminal() = 0;
};