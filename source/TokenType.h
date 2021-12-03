#pragma once

enum class TokenType
{
    BoolLiteral,
    IntegerLiteral,
    NumberLiteral,
    StringLiteral,
    UnclosedStringLiteral,
    AssignOperator,
    PlusOperator,
    Operator,
    Bracket,
    Identifier,
    Semicolon,
    EndOfLine,
    EndOfSource,
    Comment,
    Keyword
};