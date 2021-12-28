
#include "token.h"

Token::Token(Token_type type, Text_document* document, Position start, Position end)
    : type{ type }
    , document{ document }
    , range{ start, end }
{
}

Token& Token::operator=(const Token& token)
{
    type = token.type;
    document = token.document;
    range = token.range;
    return *this;
}

bool Token::is_end_statement_token()
{
    return type == Token_type::End_of_line || type == Token_type::Semicolon;
}

std::u16string Token::get_source_text()
{
    return document->get_substring(range);
}