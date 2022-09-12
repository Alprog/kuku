
#pragma once

#include <vector>
#include "operand.h"
#include "binary_operator_node.h"

namespace expr
{
	class expression
	{
		std::vector<operand> operands;
		std::vector<Binary_operator_node> operators;
	};
}