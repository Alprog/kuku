#pragma once

#include "TokenType.h"

struct Token
{
    int Start;
    int Length;
    TokenType Type;
};