#pragma once

#include <iostream>
#include "Lexer.h";
#include "Console.h"
#include "types.h"
#include "Unicode.h"
#include "TextDocument.h"

void Repl()
{
    std::cout << "kuku language 0.1" << std::endl;
    while (true)
    {
        std::cout << "> ";
        std::u16string line = Console::readline();
        if (line == u"exit")
        {
            break;
        }

        TextDocument document;
        document.lines.push_back(line);

        Lexer lexer{ document };
        lexer.process();
    }
}