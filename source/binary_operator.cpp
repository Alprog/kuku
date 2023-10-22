
#include "binary_operator.h"

std::vector<binary_operator>& get_binary_operators()
{
    static std::vector<binary_operator> operators {
        { token_type::Exponent_operator, precedence::exponentiation },

        { token_type::Multiply_Operator, precedence::multiplication },
        { token_type::Divide_Operator, precedence::multiplication },

        { token_type::Plus_operator, precedence::addition },
        { token_type::Minus_operator, precedence::addition },
        
        { token_type::Less_operator, precedence::relational },
        { token_type::Greater_operator, precedence::relational },
        { token_type::Less_or_equal_operator, precedence::relational },
        { token_type::Greater_or_equal_operator, precedence::relational },

        { token_type::Equal_operator, precedence::equality },
        { token_type::Not_equal_operator, precedence::equality },
    };

    return operators;
}