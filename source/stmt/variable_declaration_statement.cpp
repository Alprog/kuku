
#include "variable_declaration_statement.h"
#include "variable_node.h"

stmt::variable_declaration_statement::variable_declaration_statement()
    : symboled{ &variable_info }
{
}

void stmt::variable_declaration_statement::parse_internal(Parser& parser)
{
    parser.require(Token_type::Keyword_var);
    reference = parser.read_symbol_reference();

    CHECK_END_OF_STATEMENT

    parser.require(Token_type::Assign_operator);

    parser.parse_expression();
}

void stmt::variable_declaration_statement::define_symbols(statement_scope*& scope)
{
    scope->define_symbol(&definition_symbol);
}