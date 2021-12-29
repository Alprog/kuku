
#include "variable_declaration_statement_node.h"
#include "variable_node.h"

void Variable_declaration_statement_node::parse_internal(Parser& parser)
{
    parser.require_keyword(u"var");
    parser.require(Token_type::Identifier);

    CHECK_END_OF_STATEMENT

    parser.require(Token_type::Assign_operator);

    parser.parse_expression();
}
