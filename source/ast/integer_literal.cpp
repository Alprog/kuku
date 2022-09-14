
#include "integer_literal.h"

ast::integer_literal::integer_literal(token* token)
{
	auto u16string = token->get_source_text();
	const std::string u8string(std::begin(u16string), std::end(u16string));

	size_t size;
	value = std::stoi(u8string, &size, 10);
}