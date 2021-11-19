#pragma once

#include <vector>
#include "primitives.h"
#include "Streams.h"

namespace unicode
{
    void writeUTF8(character character, std::vector<byte>& bytes);
    character readUTF8(InputStream<byte>& stream);
}
