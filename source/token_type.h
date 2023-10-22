#pragma once

#include "reflectable_enum.h"

reflectable_enum(token_type,
    Bool_literal,
    Integer_literal,
    Number_literal,
    String_literal,
    Unclosed_string_literal,
    Assign_operator,
    Exponent_operator,
    Minus_operator,
    Plus_operator,
    Not_operator,
    Equal_operator,   
    Not_equal_operator,
    Less_operator,
    Greater_operator,
    Less_or_equal_operator,
    Greater_or_equal_operator,
    Divide_Operator,
    Multiply_Operator,
    Open_bracket,
    Close_bracket,
    Open_brace,
    Close_brace,
    Open_parenthesis,
    Close_parenthesis,
    Identifier,
    Colon,
    Semicolon,
    Dot,
    Comma,
    End_of_line,
    End_of_source,
    Comment,

    Keyword_if,
    Keyword_and,
    Keyword_class,
    Keyword_do,
    Keyword_else,
    Keyword_end,
    Keyword_for,
    Keyword_function,
    Keyword_or,
    Keyword_return,
    Keyword_then,
    Keyword_var,
    Keyword_while    
);