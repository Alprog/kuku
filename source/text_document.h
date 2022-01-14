#pragma once

#include <vector>
#include <string>

#include "streams.h"
#include "lsp/range.h"

class Text_document
{
public:
    Text_document();
    Text_document(Input_stream<utf16unit>& stream);

    std::vector<std::u16string> lines;

    utf16unit get_character(lsp::position position);
    std::u16string get_substring(lsp::range range);
};