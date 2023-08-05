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

void repl()
{
    std::cout << "kuku language 0.1" << std::endl;
    
    virtual_machine machine;

    while (true)
    {
        std::cout << "> ";
        std::u16string line = console::read_line();
        if (line == u"exit")
        {
            break;
        }
        
        source_project project;
        project.add_memory_snippet(line);
        project.process_all();

        project.get_module("memory")->compile_and_run();
        //machine.perform();

        

        project.clear_all();
    }
}