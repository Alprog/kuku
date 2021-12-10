
#include "SyntaxNode.h"
#include "Token.h"

class SingleTokenSyntaxNode : SyntaxNode
{
public:
	Token* nodeToken;
};