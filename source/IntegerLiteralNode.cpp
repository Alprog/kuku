
#include "IntegerLiteralNode.h"

IntegerLiteralNode::IntegerLiteralNode(Token* token)
{
	auto u16string = token->getSourceText();
	const std::string u8string(std::begin(u16string), std::end(u16string));

	size_t size;
	value = std::stoi(u8string, &size, 10);
}