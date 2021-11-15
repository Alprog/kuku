
#include "TextDocument.h"

uint16_t TextDocument::getCharacter(Position position)
{
    if (position.line < lines.size())
    {
        auto& line = lines[position.line];
        if (position.character < line.size())
        {
            return line[position.character];
        }
        else
        {
            return '\n';
        }
    }
    else
    {
        return '\0';
    }
}

std::u16string TextDocument::getSubstring(Range range)
{
    auto l1 = range.start.line;
    auto l2 = range.start.line;
    if (l1 == l2)
    {
        if (l1 < lines.size())
        {
            auto c1 = range.start.character;
            auto c2 = range.end.character;
            return lines[l1].substr(c1, c2 - c1);
        }
    }

    throw std::exception("not implemented");
}