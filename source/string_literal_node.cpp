
#include "string_literal_node.h"

String_literal_node::String_literal_node(token* token)
{
	this->node_token = token;

	token->get_source_text();
}