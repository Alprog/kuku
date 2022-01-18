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
    
    Virtual_machine machine;

    while (true)
    {
        std::cout << "> ";
        std::u16string line = Console::read_line();
        if (line == u"exit")
        {
            break;
        }
        
        source_project project;
        project.add_memory_snippet(line);
        project.process_all();

        //machine.perform();

        project.clear_all();
    }
}