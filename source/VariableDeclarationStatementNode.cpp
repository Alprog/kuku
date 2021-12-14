
#include "VariableDeclarationStatementNode.h"
#include "VariableNode.h"

bool VariableDeclarationStatementNode::parseInternal(Parser& parser)
{
    if (parser.matchKeyword(u"var"))
    {
        if (parser.current.type == TokenType::Identifier)
        {
            auto node = new VariableNode();
            node->name = parser.current.getSourceText();
            parser.next(false);

            if (parser.current.isEndStatementToken())
            {
                parser.next(false);
                return true;
            }
        }
    }

    return false;
}
