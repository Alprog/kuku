#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "types.h"
#include "TextDocument.h"
#include "SourceIterator.h"

class Lexer
{
public:
    Lexer(TextDocument& textDocument);
    void process();

private:
    Token getNextToken();

    Token createToken(SourceIterator start, TokenType type);

    TextDocument& textDocument;
    SourceIterator it;

    Position captureStart;
    Position captureEnd;
};