#pragma once

enum class TokenType
{
    BoolLiteral,
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