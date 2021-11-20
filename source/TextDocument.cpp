
#include "TextDocument.h"

TextDocument::TextDocument()
{

}

TextDocument::TextDocument(InputStream<utf16unit>& stream)
{
    std::vector<utf16unit> line;

    auto flushLine = [this, &line]()
    {
        lines.push_back({ std::begin(line), std::end(line) });
        line.clear();
    };


    utf16unit unit, prevUnit = 0;
    while (stream.next(unit))
    {
        if (unit == '\r')
        {
            flushLine();
        }
        if (unit == '\n')
        {
            if (prevUnit != '\r')
            {
                flushLine();
            }
        }
        else
        {
            line.push_back(unit);
        }
        prevUnit = unit;
    }

    flushLine();
}

utf16unit TextDocument::getCharacter(Position position)
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