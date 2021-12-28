
#include "source_iterator.h"
#include "unicode.h"
#include "text_document.h"

Source_iterator::Source_iterator(Text_document& text_document)
    : text_document{ text_document }
    , position{ 0, 0 }
{
}

utf16unit Source_iterator::operator*()
{
    return text_document.get_character(position);
}

Source_iterator& Source_iterator::operator++()
{
    position.character++;

    if (position.line < text_document.lines.size())
    {
        auto& line = text_document.lines[position.line];
        if (position.character > line.size())
        {
            position.line++;
            position.character = 0;
        }
    }

    return *this;
}

Source_iterator Source_iterator::operator++(int)
{
    auto old = *this;
    operator++();
    return old;
}
