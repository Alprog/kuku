#pragma once

#include "types.h"
#include <vector>
#include <deque>
#include <string>
#include "streams.h"

namespace unicode
{
    bool read_character(Input_stream<utf8unit>& stream, character& character);
    void write_character(Output_stream<utf8unit>& stream, character character);

    bool read_character(Input_stream<utf16unit>& stream, character& character);
    void write_character(Output_stream<utf16unit>& stream, character character);

    std::u8string to_utf8(const std::u16string&);
    std::u16string to_utf16(const std::u8string&);
}
