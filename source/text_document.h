#pragma once

#include <vector>
#include <string>

#include "range.h"
#include "streams.h"

class Text_document
{
public:
    Text_document();
    Text_document(Input_stream<utf16unit>& stream);

    std::vector<std::u16string> lines;

    utf16unit get_character(Position position);
    std::u16string get_substring(Range range);
};