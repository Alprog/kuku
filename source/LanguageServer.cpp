
#include "LanguageServer.h"

#include <iostream>

void language_server::run()
{
    std::string message;
    while (true)
    {
        char c;
        std::cin >> c;
        message += c;
    }
}