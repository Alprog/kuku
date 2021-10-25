#pragma once

enum class TokenType
{
    IntegerLiteral,
    NumberLiteral,
    StringLiteral,
    Operator,
    Bracket,
    UpperCaseIdentifier,
    LowerCaseIdentifier,
    Semicolon,
    EndOfLine,
    EndOfSource
};