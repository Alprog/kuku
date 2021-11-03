#pragma once

#include <map>
#include <string>
#include "Terminal.h"
#include "NonTerminal.h"

class Grammar
{
public:
    void RegTerminals(std::string terminalString);

    template <typename... Args>
    void RegNonTerminal(std::string type, Args... args)
    {
        RegNonTerminal(type, { args... });
    }

    void RegNonTerminal(std::string type, std::vector<std::string> productions);

    void Finish();

private:
    std::map<std::string, Symbol*> Symbols;
    std::map<std::string, std::vector<std::string>> TextProductions;
};