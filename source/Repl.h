#pragma once

#include <iostream>
#include "lexer.h";
#include "console.h"
#include "types.h"
#include "unicode.h"
#include "text_document.h"
#include <sstream>

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
        
        std::basic_istringstream stringStream{ line };
        BasicInputStream basicStream{ stringStream };
        TextDocument document{ basicStream };

        Lexer lexer{ document };
        lexer.process();
    }
}