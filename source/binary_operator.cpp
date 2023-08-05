
#include "binary_operator.h"

std::vector<binary_operator>& get_binary_operators()
{
    static std::vector<binary_operator> operators {
        { token_type::Exponent_operator, precedence::exponentiation },

        { token_type::Multiply_Operator, precedence::multiplication },
        { token_type::Divide_Operator, precedence::multiplication },

        { token_type::Plus_operator, precedence::addition },
        { token_type::Minus_operator, precedence::addition },
    };

    return operators;
}