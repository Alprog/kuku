
#include "token.h"

token::token(Token_type type, Text_document* document, lsp::position start, lsp::position end)
    : type{ type }
    , document{ document }
    , range{ start, end }
{
}

token& token::operator=(const token& token)
{
    type = token.type;
    document = token.document;
    range = token.range;
    return *this;
}

bool token::is_end_statement_token()
{
    return type == Token_type::End_of_line || type == Token_type::Semicolon;
}

std::u8string token::get_hover_text()
{
    return u8"**token:** "_s + get_u8name(type) + u8"\r\n" +
           u8"**Content:** " + unicode::to_utf8(get_source_text());
}

std::u16string token::get_source_text()
{
    return document->get_substring(range);
}