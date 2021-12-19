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
    OpenBracket,
    CloseBracket,
    OpenBrace,
    CloseBrace,
    OpenChevron,
    CloseChevron,
    OpenParenthesis,
    CloseParenthesis,
    Identifier,
    Semicolon,
    EndOfLine,
    EndOfSource,
    Comment,
    Keyword
};