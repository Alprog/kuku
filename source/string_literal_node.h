
#pragma once

#include "single_token_syntax_node.h"
#include "string.h"

class String_literal_node : public Single_token_syntax_node
{
public:
	String_literal_node(token* token);
};