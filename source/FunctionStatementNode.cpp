
#include "FunctionStatementNode.h"

bool FunctionStatementNode::parseInternal(Parser& parser)
{
	parser.requireKeyword(u"function");

	
	parser.require(TokenType::Identifier);

	parser.require(TokenType::OpenParenthesis);
	parser.require(TokenType::CloseParenthesis);

	if (parser.matchEndOfStatement()) return true;

	parser.require(TokenType::Semicolon);
	parser.require(TokenType::Identifier);

	if (parser.matchEndOfStatement()) return true;
	
	return false;
}