
#include "Grammar.h"
#include <string>
#include <iostream>
#include "utils.h"

void Grammar::RegTerminals(std::string terminalString)
{
    for (auto& name : split(terminalString, " "))
    {
        Symbols[name] = new Terminal{ name };
    }
}

void Grammar::RegNonTerminal(std::string name, std::vector<std::string> productions)
{
    Symbols[name] = new NonTerminal{ name };
    TextProductions[name] = productions;
}

void Grammar::Finish() 
{
    for (auto pair : TextProductions)
    {
        auto name = pair.first;
        auto nonTerminal = static_cast<NonTerminal*>(Symbols[name]);
        for (auto textProduction : pair.second)
        {
            Production production;

            for (auto& name : split(textProduction, " "))
            {
                auto it = Symbols.find(name);
                if (it == std::end(Symbols))
                {
                    std::cout << "Error! Undefined symbol " << name << std::endl;
                }
                else
                {
                    production.Symbols.push_back(it->second);
                }
            }
            
            nonTerminal->Productions.push_back(production);
        }
    }
}