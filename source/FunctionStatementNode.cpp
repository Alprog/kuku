
#include "FunctionStatementNode.h"

bool FunctionStatementNode::parseInternal(Parser& parser)
{
	if (parser.matchKeyword(u"function"))
	{
		if (parser.match(TokenType::Identifier))
		{
			if (parser.match(TokenType::Bracket) && parser.match(TokenType::Bracket))
			{
				if (parser.matchEndOfStatement()) return true;

				if (parser.match(TokenType::Semicolon) && parser.match(TokenType::Identifier))
				{
					if (parser.matchEndOfStatement()) return true;
				}
			}
		}
	}
	return false;
}