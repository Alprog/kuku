#pragma once

#include <iostream>
#include "Lexer.h";
#include "Console.h"
#include "primitives.h"
#include "Unicode.h"

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

        std::vector<byte> bytes;
        for (auto& c : line)
        {
            unicode::writeUTF8(c, bytes);
        }

        Lexer lexer{ bytes };
        lexer.process();
    }
}