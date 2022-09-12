
#include "string_literal_node.h"

ast::string_literal::string_literal(token* token)
{
	this->node_token = token;

	token->get_source_text();
}