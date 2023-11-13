#pragma once

#include "reflectable_enum.h"

reflectable_enum(token_type, int,
    bool_literal,
    integer_literal,
    number_literal,
    string_literal,
    unclosed_string_literal,
    assign_operator,
    exponent_operator,
    minus_operator,
    plus_operator,
    not_operator,
    equal_operator,
    not_equal_operator,
    less_operator,
    greater_operator,
    less_or_equal_operator,
    greater_or_equal_operator,
    divide_Operator,
    multiply_Operator,
    open_bracket,
    close_bracket,
    open_brace,
    close_brace,
    open_parenthesis,
    close_parenthesis,
    identifier,
    colon,
    semicolon,
    dot,
    comma,
    end_of_line,
    end_of_source,
    comment,

    keyword_and,
    keyword_break,
    keyword_class,
    keyword_continue,
    keyword_do,
    keyword_else,
    keyword_end,
    keyword_for,
    keyword_function,
    keyword_if,
    keyword_or,
    keyword_return,
    keyword_then,
    keyword_var,
    keyword_while    
);