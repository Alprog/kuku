
#include "variable_declaration_statement.h"

void stmt::variable_declaration_statement::parse_internal(Parser& parser)
{
    parser.require(Token_type::Keyword_var);
    parse_symbol(parser);

    CHECK_END_OF_STATEMENT

    parser.require(Token_type::Assign_operator);
    expression = parser.parse_expression();
}

void stmt::variable_declaration_statement::semantic_analyze()
{
    if (expression != nullptr)
    {
        expression->semantic_analyze(*this);
    }
}

void stmt::variable_declaration_statement::define_symbols(statement_scope* scope)
{
    scope->define_symbol(symbol);
}