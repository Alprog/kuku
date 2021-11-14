#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "primitives.h"
#include "TextDocument.h"
#include "SourceIterator.h"

class Lexer
{
public:
    Lexer(TextDocument& textDocument);
    void process();

private:
    Token getNextToken();

    Token createSingleToken(TokenType type);
    Token createToken(Position startPosition, TokenType type);

    TextDocument& textDocument;
    SourceIterator sourceIterator;

    Position captureStart;
    Position captureEnd;
};