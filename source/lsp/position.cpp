
#include "position.h"

namespace lsp
{
    position::position(int line, int character)
        : line{ line }
        , character{ character }
    {
    }

    std::u16string position::to_str()
    {
        auto asciiStr = "{" + std::to_string(line) + ":" + std::to_string(character) + "}";
        return std::u16string(std::begin(asciiStr), std::end(asciiStr));
    }

    std::strong_ordering position::operator<=>(const position& other) const
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
}