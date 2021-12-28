#pragma once

#include "token_type.h"
#include "range.h"
#include "text_document.h"
#include <string>

class SyntaxNode;

struct Token
{
    Token_type type;
    Text_document* document;
    Range range;

    SyntaxNode* syntax_node;

    Token& operator=(const Token& token);
    Token(Token_type type, Text_document* document, Position start, Position end);

    bool is_end_statement_token();

    std::u16string get_source_text();
};