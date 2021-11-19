
#include "SourceIterator.h"
#include "Unicode.h"
#include "TextDocument.h"

SourceIterator::SourceIterator(TextDocument& textDocument)
    : textDocument{ textDocument }
    , position{ 0, 0 }
{
}

utf16unit SourceIterator::operator*()
{
    return textDocument.getCharacter(position);
}

SourceIterator& SourceIterator::operator++()
{
    position.character++;

    if (position.line < textDocument.lines.size())
    {
        auto& line = textDocument.lines[position.line];
        if (position.character > line.size())
        {
            position.line++;
            position.character = 0;
        }
    }

    return *this;
}

SourceIterator SourceIterator::operator++(int)
{
    auto old = *this;
    operator++();
    return old;
}
