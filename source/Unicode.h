#pragma once

#include "types.h"
#include <vector>
#include <queue>
#include "streams.h"

namespace unicode
{
    void writeUTF8(character character, std::vector<byte>& bytes);
    character readUTF8(InputStream<byte>& stream);

    void writeUTF16(character character, std::queue<utf16unit>& units);
    character readUTF16(InputStream<utf16unit>& stream);
}
