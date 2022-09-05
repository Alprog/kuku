#pragma once

#include "token_type.h"
#include "lsp/range.h"
#include "text_document.h"
#include <string>
#include "symbol_reference.h"

struct token
{
    Token_type type;
    Text_document* document;
    lsp::range range;

    symbol_reference symbol_reference;

    token& operator=(const token& token);
    token(Token_type type, Text_document* document, lsp::position start, lsp::position end);

    bool is_end_statement_token();

    std::u8string get_hover_text();

    std::u16string get_source_text();
};