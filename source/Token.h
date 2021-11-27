#pragma once

#include "TokenType.h"
#include "Range.h"
#include "TextDocument.h"
#include <string>

struct Token
{
    TokenType type;
    TextDocument* document;
    Range range;

    Token();

    Token& operator=(const Token& token);
    Token(TokenType type, TextDocument* document, Position start, Position end);

    std::u16string getSourceText();
};