
#pragma once

#include <vector>
#include "operand.h"
#include "binary_operator.h"

namespace ast
{
	class expression
	{
		std::vector<operand> operands;
		std::vector<binary_operator> operators;
	};
}