
#include "StatementNode.h"

StatementNode* StatementNode::init(Parser& parser)
{
	this->startToken = &parser.current;
	this->IsValid = parseInternal(parser);
	if (!this->IsValid)
	{
		this->errorText = u"unexpected token '" + parser.current.getSourceText() + u"' at " + parser.current.range.start.toStr();
		while (!parser.current.isEndStatementToken()) parser.next(false); // panic mode
		parser.next(false);
	}

	return this;
}

int StatementNode::getNestingLevel()
{
	return 0;
}