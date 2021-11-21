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

    Token finishOneLineComment(SourceIterator startIt);
    Token finishMultilineComment(SourceIterator startIt, utf16unit endSymbol1, utf16unit endSymbol2);
    Token finishString(SourceIterator startIt, utf16unit endQuote, bool escaping);

    bool moveTo(utf16unit endSymbol);
    bool moveToEscaped(utf16unit endSymbol);

    Token createToken(SourceIterator start, TokenType type);

    TextDocument& textDocument;
    SourceIterator it;

    Position captureStart;
    Position captureEnd;
};