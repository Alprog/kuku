
#include <iostream>
#include <string>
#include <locale>

#include "Scanner.h";

#include "Console.h"

int wmain(int argc, const wchar_t* argv[])
{
    while (true)
    {
        std::cout << "> ";
        std::wstring line = Console::readline();
        if (line == L"exit")
        {
            break;
        }
        Scanner scanner{ line };
        scanner.process();
    }
    return 0;
}
