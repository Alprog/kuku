
#include "EndStatementNode.h"

bool EndStatementNode::parseInternal(Parser& parser)
{
	if (parser.matchKeyword(u"end"))
	{
		if (parser.matchEndOfStatement()) return true;
	}
	return false;
}