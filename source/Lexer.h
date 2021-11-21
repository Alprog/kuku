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

    Token finishMultilineComment(SourceIterator startIt);
    Token finishString(SourceIterator startIt, utf16unit endQuote, bool escaping);

    bool moveTo(utf16unit endQuote);
    bool moveToEscaped(utf16unit endQuote);

    Token createToken(SourceIterator start, TokenType type);

    TextDocument& textDocument;
    SourceIterator it;

    Position captureStart;
    Position captureEnd;
};