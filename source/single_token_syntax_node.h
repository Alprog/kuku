
#include "syntax_node.h"
#include "token.h"

class Single_token_syntax_node : public Syntax_node
{
public:
	token* node_token;
};