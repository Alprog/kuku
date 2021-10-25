#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"

class Scanner
{
public:
    Scanner();
    void process(std::wstring line);

private:
    void flushToken(TokenType type);

    int tokenStartIndex;
    std::vector<Token> tokens;
};