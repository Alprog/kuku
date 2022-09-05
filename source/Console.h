#pragma once

#include <string>
#include <conio.h>

namespace Console
{
    std::u16string read_line();

    void write_line(std::string line);
    void write_line(std::u8string line);
    void write_line(std::u16string line);
}
