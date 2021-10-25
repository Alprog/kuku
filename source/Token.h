#pragma once

#include "TokenType.h"

struct Token
{
    int Start;
    int Length;
    TokenType Type;

    Token(int start, int length, TokenType type)
    {
        this->Start = start;
        this->Length = length;
        this->Type = type;
    }
};