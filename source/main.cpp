
#include <iostream>
#include <string>
#include "Repl.h"

void printHelp()
{
    std::cout << "usage:" << std::endl;
    std::cout << "-h | --help: print help" << std::endl;
    std::cout << "repl: enter repl mode" << std::endl;
}

int main(int argc, const char* argv[])
{
    std::string command{ argc > 1 ? argv[1] : "repl" };


    if (command == "-h" || command == "--help")
    {
        printHelp();
    }
    else if (command == "repl")
    {
        Repl();
    }
    else
    {
        std::cout << "unknown command: " << command << std::endl;
        printHelp();
    }

    return 0;
}
