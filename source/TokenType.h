#pragma once

enum class TokenType
{
    IntegerLiteral,
    NumberLiteral,
    StringLiteral,
    UnclosedStringLiteral,
    Operator,
    Bracket,
    UpperCaseIdentifier,
    LowerCaseIdentifier,
    Semicolon,
    EndOfLine,
    EndOfSource,
    Comment
};