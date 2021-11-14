#pragma once

#include <vector>
#include <string>

#include "Position.h"

class TextDocument
{
public:
    std::vector<std::u16string> lines;

    uint16_t getCharacter(Position position);
};