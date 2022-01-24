
#pragma once

#include "single_token_syntax_node.h"

class Integer_literal_node : Single_token_syntax_node
{
public:
	Integer_literal_node(token* token);

	int value;
};