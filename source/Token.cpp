
#include "token.h"

Token::Token(TokenType type, TextDocument* document, Position start, Position end)
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

bool Token::isEndStatementToken()
{
    return type == TokenType::EndOfLine || type == TokenType::Semicolon;
}

std::u16string Token::getSourceText()
{
    return document->getSubstring(range);
}