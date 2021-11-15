
#include "Console.h"

namespace Console
{
    std::u16string readline()
    {
        wchar_t buffer[0x1000];
        std::size_t numRead = 0;
        _cgetws_s(buffer, &numRead);
        std::wstring line(buffer, numRead);
        return std::u16string(std::begin(line), std::end(line));
    }

    void writeline(std::u16string line)
    {
        _cputws(std::wstring(std::begin(line), std::end(line)).c_str());
        _cputws(L"\n");
    }
}
