#pragma once

#include "TokenType.h"
#include "Range.h"

struct Token
{
    Range range;
    TokenType type;

    Token(Position start, Position end, TokenType type)
        : range {start, end}
        , type {type}
    {
    }
};