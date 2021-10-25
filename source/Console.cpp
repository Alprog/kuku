
#include "Console.h"

namespace Console
{
    std::wstring readline()
    {
        wchar_t buffer[0x1000];
        std::size_t numRead = 0;
        _cgetws_s(buffer, &numRead);
        return std::wstring(buffer, numRead);
    }

    void writeline(std::wstring line)
    {
        _cputws(line.c_str());
        _cputws(L"\n");
    }
}
