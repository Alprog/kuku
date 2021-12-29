
#include "variable_declaration_statement_node.h"
#include "variable_node.h"

bool Variable_declaration_statement_node::parse_internal(Parser& parser)
{
    if (parser.match_keyword(u"var"))
    {
        if (parser.current->type == Token_type::Identifier)
        {
            auto node = new Variable_node();
            node->name = parser.current->get_source_text();
            parser.next();

            if (parser.current->is_end_statement_token())
            {
                parser.next();
                return true;
            }
        }
    }

    return false;
}
