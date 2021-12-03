#pragma once

#include "TokenType.h"
#include "Range.h"
#include "TextDocument.h"
#include <string>

class SyntaxNode;

struct Token
{
    TokenType type;
    TextDocument* document;
    Range range;

    SyntaxNode* syntaxNode;

    Token& operator=(const Token& token);
    Token(TokenType type, TextDocument* document, Position start, Position end);

    std::u16string getSourceText();
};