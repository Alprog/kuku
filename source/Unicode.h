#pragma once

#include "types.h"
#include <vector>
#include <queue>
#include "streams.h"

namespace unicode
{
    void write_utf8(character character, std::vector<utf8unit>& bytes);
    character read_utf8(Input_stream<utf8unit>& stream);

    void write_utf16(character character, std::queue<utf16unit>& units);
    character read_utf16(Input_stream<utf16unit>& stream);
}
