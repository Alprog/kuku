#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"

class Lexer
{
public:
    Lexer(std::wstring sourceText);
    void process();

private:
    Token getNextToken();
    Token createToken(TokenType type, int length = 1);

    std::wstring sourceText;
    int currentIndex;
};