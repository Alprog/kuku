#pragma once

#include <string>
#include <conio.h>

namespace Console
{
    std::u16string readline();

    void writeline(std::u16string line);
}
