
#pragma once

#include "single_token_syntax_node.h"

class Binary_operator_node : public Single_token_syntax_node
{
public:
	Binary_operator_node(Token* token);
};