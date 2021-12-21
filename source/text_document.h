#pragma once

#include <vector>
#include <string>

#include "range.h"
#include "streams.h"

class TextDocument
{
public:
    TextDocument();
    TextDocument(InputStream<utf16unit>& stream);

    std::vector<std::u16string> lines;

    utf16unit getCharacter(Position position);
    std::u16string getSubstring(Range range);
};