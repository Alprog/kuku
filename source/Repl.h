#pragma once

#include <iostream>
#include "lexer.h";
#include "console.h"
#include "types.h"
#include "unicode.h"
#include "text_document.h"
#include <sstream>

#include "source_project.h"
#include "virtual_machine.h"

void Repl()
{
    std::cout << "kuku language 0.1" << std::endl;
    
    Source_project project;
    Virtual_machine machine;

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