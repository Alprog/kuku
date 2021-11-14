#pragma once

#include <iostream>
#include "Lexer.h";
#include "Console.h"
#include "primitives.h"
#include "Unicode.h"
#include "TextDocument.h"

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

        auto u16string = std::u16string(std::begin(line), std::end(line));

        TextDocument document;
        document.lines.push_back(u16string);

        Lexer lexer{ document };
        lexer.process();
    }
}