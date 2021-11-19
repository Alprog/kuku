#pragma once

#include <vector>
#include <string>

#include "Range.h"
#include "Streams.h"

class TextDocument
{
public:
    TextDocument();
    TextDocument(InputStream<utf16unit>& stream);

    std::vector<std::u16string> lines;

    utf16unit getCharacter(Position position);
    std::u16string getSubstring(Range range);
};