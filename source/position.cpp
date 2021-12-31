
#include "position.h"

Position::Position(int line, int character)
    : line{ line }
    , character{ character }
{
}

std::u16string Position::to_str()
{
    auto asciiStr = "{" + std::to_string(line) + ":" + std::to_string(character) + "}";
    return std::u16string(std::begin(asciiStr), std::end(asciiStr));
}

std::strong_ordering Position::operator<=>(const Position& other) const
{
    auto line_order = line <=> other.line;
    if (line_order == std::strong_ordering::equal)
    {
        return character <=> other.character;
    }
    else
    {
        return line_order;
    }
}