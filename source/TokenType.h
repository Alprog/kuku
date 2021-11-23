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
    Identifier,
    Semicolon,
    EndOfLine,
    EndOfSource,
    Comment,
    Keyword
};