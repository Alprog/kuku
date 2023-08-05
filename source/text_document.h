#pragma once

#include <vector>
#include <string>

#include "streams.h"
#include "lsp/range.h"
#include "lsp/text_document_content_change_event.h"

class text_document
{
public:
    text_document();
    text_document(Input_stream<utf16unit>& stream);

    std::vector<std::u16string> lines;

    utf16unit get_character(lsp::position position);
    std::u16string get_substring(lsp::range range);

    void change_content(lsp::text_document_content_change_event& event);
};