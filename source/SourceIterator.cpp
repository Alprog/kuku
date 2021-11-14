
#include "SourceIterator.h"
#include "Unicode.h"
#include "TextDocument.h"

SourceIterator::SourceIterator(TextDocument& textDocument)
    : textDocument{ textDocument }
    , position{ 0, 0 }
{
}

uint16_t SourceIterator::operator*()
{
    return textDocument.getCharacter(position);
}

void SourceIterator::next()
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
}
