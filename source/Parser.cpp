
#include "parser.h"
#include "console.h"
#include "variable_node.h"
#include "binary_operator_node.h"
#include "variable_declaration_statement_node.h"
#include "assign_statement_node.h"
#include "invalid_statement_node.h"
#include "statement_node.h"
#include "end_statement_node.h"
#include "function_statement_node.h"
#include "class_statement_node.h"
#include "unexepected_error.h"

Parser::Parser(Lexer& lexer)
	: lexer{ lexer }
    , current{ TokenType::EndOfLine, nullptr, { 0,0 }, { 0,0 } }
{
}

void Parser::process()
{
    next(true);
    while (current.type != TokenType::EndOfSource)
    {
        statements.push_back(parseStatement());
    }
}

void Parser::next(bool skipNewLines)
{
    current = lexer.getNextToken();
    while (current.type == TokenType::Comment || (skipNewLines && current.type == TokenType::EndOfLine))
    {
        current = lexer.getNextToken();
    }
}

Token* startToken;

template <typename T>
T* Parser::createNode()
{
    auto node = new T();
    node->init(*this);
    return node;
}

StatementNode* Parser::parseStatement()
{
    startToken = &current;

    if (current.type == TokenType::Keyword)
    {
        if (current.getSourceText() == u"var")
        {
            return createNode<VariableDeclarationStatementNode>();
        }
        else if (current.getSourceText() == u"end")
        {
            return createNode<EndStatementNode>();
        }
        else if (current.getSourceText() == u"function")
        {
            return createNode<FunctionStatementNode>();
        }
        else if (current.getSourceText() == u"class")
        {
            return createNode<ClassStatementNode>();
        }
    }
    else if (current.type == TokenType::Identifier)
    {
        auto id = current.getSourceText();
        Console::writeline(id);

        next(false);
        if (current.type == TokenType::AssignOperator)
        {
            auto node = new BinaryOperatorNode(&current);
            next(false);

            if (current.type == TokenType::IntegerLiteral)
            {
                next(false);
                if (current.type == TokenType::EndOfLine)
                {
                    next(false);
                    return new AssignStatementNode();
                }
            }

        }
    }

    return (new InvalidStatementNode())->init(*this);
}

void Parser::parseExpression()
{

}

bool Parser::require(TokenType type)
{
    if (!match(type))
    {
        throw UnexpectedError();
    }
}

bool Parser::match(TokenType type)
{
    if (current.type == type)
    {
        next(false);
        return true;
    }
    return false;
}

bool Parser::requireKeyword(std::u16string keyword)
{
    if (!matchKeyword(keyword))
    {
        throw UnexpectedError();
    }
}

bool Parser::matchKeyword(std::u16string keyword)
{
    if (current.type == TokenType::Keyword && current.getSourceText() == keyword)
    {
        next(false);
        return true;
    }
    return false;
}

bool Parser::matchEndOfStatement()
{
    if (current.isEndStatementToken())
    {
        next(false);
        return true;
    }
    return false;
}