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
    Token getNextToken();

public:
    Token finishLineComment(SourceIterator startIt);
    Token finishBlockComment(SourceIterator startIt);
    Token finishBindingBlockComment(SourceIterator startIt);
    Token finishString(SourceIterator startIt, utf16unit endQuote, bool escaping);

    bool match(utf16unit symbol);

    bool moveAfter(utf16unit endSymbol);
    bool moveAfterEscaped(utf16unit endSymbol);

    Token createToken(SourceIterator start, TokenType type);

    TextDocument& textDocument;
    SourceIterator it;

    Position captureStart;
    Position captureEnd;
};