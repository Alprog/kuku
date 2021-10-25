
#include "Scanner.h"
#include "Console.h"

Scanner::Scanner()
    : tokenStartIndex{0}
{
}

void Scanner::process(std::wstring line)
{
    auto tokenStart = 0;
    
    int current = 0;
    while (current < line.size())
    {
        wchar_t c = line[current];

        
        Console::writeline(std::wstring{ c });

        current++;
    }

    std::wstring result = L"token count: " + std::to_wstring(tokens.size());
    Console::writeline(result);
}

void Scanner::flushToken(TokenType type)
{
}
