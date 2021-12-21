#pragma once

#include "token_type.h"
#include "range.h"
#include "text_document.h"
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

    bool isEndStatementToken();

    std::u16string getSourceText();
};