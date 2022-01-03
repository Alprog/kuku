#pragma once

#include "types.h"
#include <vector>
#include <queue>
#include <string>
#include "streams.h"

namespace unicode
{
    void write_utf8(character character, std::vector<utf8unit>& bytes);
    character read_utf8(Input_stream<utf8unit>& stream);

    void write_utf16(character character, std::queue<utf16unit>& units);
    character read_utf16(Input_stream<utf16unit>& stream);

    std::u8string to_utf8(std::u16string);
    std::u16string to_utf16(std::u8string);
}
