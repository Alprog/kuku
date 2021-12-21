
#include "class_statement_node.h"

bool ClassStatementNode::parseInternal(Parser& parser)
{
	if (parser.matchKeyword(u"class"))
	{
		if (parser.match(TokenType::Identifier))
		{
			if (parser.matchEndOfStatement()) return true;
		}
	}
	return false;
}