#pragma once

#include "token_type.h"
#include "lsp/range.h"
#include "text_document.h"
#include <string>

class Symbol;

struct Token
{
    Token_type type;
    Text_document* document;
    lsp::range range;

    Symbol* symbol;

    Token& operator=(const Token& token);
    Token(Token_type type, Text_document* document, lsp::position start, lsp::position end);

    bool is_end_statement_token();

    std::u8string get_hover_text();

    std::u16string get_source_text();
};