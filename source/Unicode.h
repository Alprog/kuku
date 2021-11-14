#pragma once

#include <vector>
#include "primitives.h"

namespace unicode
{
    void writeUTF8(character character, std::vector<byte>& bytes);
    character readUTF8(std::vector<byte>& bytes, size_t& index);
}
