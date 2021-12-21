
#include "syntax_node.h"
#include "token.h"

class SingleTokenSyntaxNode : SyntaxNode
{
public:
	Token* nodeToken;
};