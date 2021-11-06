#pragma once

#include <iostream>
#include "Lexer.h";
#include "Console.h"

void Repl()
{
    std::cout << "kuku language 0.1" << std::endl;
    while (true)
    {
        std::cout << "> ";
        std::wstring line = Console::readline();
        if (line == L"exit")
        {
            break;
        }
        Lexer lexer{ line };
        lexer.process();
    }
}