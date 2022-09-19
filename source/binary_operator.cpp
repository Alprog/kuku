
#include "binary_operator.h"

std::vector<binary_operator>& get_binary_operators()
{
    static std::vector<binary_operator> operators {
         { Token_type::Exponent_operator, precedence::exponentiation },

        { Token_type::Multiply_Operator, precedence::multiplication },
        { Token_type::Divide_Operator, precedence::multiplication },

        { Token_type::Plus_operator, precedence::addition },
        { Token_type::Minus_operator, precedence::addition },
    };

    return operators;
}