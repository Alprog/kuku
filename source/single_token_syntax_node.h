
#include "syntax_node.h"
#include "token.h"

class Single_token_syntax_node : Syntax_node
{
public:
	Token* node_token;
};