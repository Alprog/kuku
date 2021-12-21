#pragma once

#include <string>
#include <vector>
#include "token.h"
#include "token_type.h"
#include "types.h"
#include "text_document.h"
#include "source_iterator.h"

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