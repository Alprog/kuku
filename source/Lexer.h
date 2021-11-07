#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "primitives.h"
#include "Encoder.h"

class Lexer
{
public:
    Lexer(std::vector<byte>& bytes);
    void process();

private:
    Token getNextToken();
    Token createToken(TokenType type, int length = 1);

    Encoder encoder;
    std::wstring sourceText;
    int currentIndex;
};