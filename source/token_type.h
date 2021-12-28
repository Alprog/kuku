#pragma once

enum class Token_type
{
    Bool_literal,
    Integer_literal,
    Number_literal,
    String_literal,
    Unclosed_string_literal,
    Assign_operator,
    Plus_sign,
    Operator,
    Open_bracket,
    Close_bracket,
    Open_brace,
    Close_brace,
    Open_chevron,
    Close_chevron,
    Open_parenthesis,
    Close_parenthesis,
    Identifier,
    Semicolon,
    End_of_line,
    End_of_source,
    Comment,
    Keyword
};