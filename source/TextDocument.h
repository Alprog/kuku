#pragma once

#include <vector>
#include <string>

#include "Range.h"

class TextDocument
{
public:
    std::vector<std::u16string> lines;

    uint16_t getCharacter(Position position);
    std::u16string getSubstring(Range range);
};