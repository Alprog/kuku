#pragma once

#include "token_type.h"
#include "range.h"
#include "text_document.h"
#include <string>

class Symbol;

struct Token
{
    Token_type type;
    Text_document* document;
    Range range;

    Symbol* symbol;

    Token& operator=(const Token& token);
    Token(Token_type type, Text_document* document, Position start, Position end);

    bool is_end_statement_token();

    std::u8string get_hover_text();

    std::u16string get_source_text();
};