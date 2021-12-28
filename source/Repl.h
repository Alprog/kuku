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
        std::u16string line = Console::read_line();
        if (line == u"exit")
        {
            break;
        }
        
        std::basic_istringstream string_stream{ line };
        Basic_input_stream basic_stream{ string_stream };
        Text_document document{ basic_stream };

        Lexer lexer{ document };
        lexer.process();
    }
}