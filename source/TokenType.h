#pragma once

enum class TokenType
{
    BoolLiteral,
    IntegerLiteral,
    NumberLiteral,
    StringLiteral,
    UnclosedStringLiteral,
    AssignOperator,
    PlusSign,
    Operator,
    Bracket,
    Identifier,
    Semicolon,
    EndOfLine,
    EndOfSource,
    Comment,
    Keyword
};