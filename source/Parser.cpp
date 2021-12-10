
#include "Parser.h"
#include "Console.h"
#include "VariableNode.h"
#include "BinaryOperatorNode.h"
#include "VariableDeclarationNode.h"
#include "AssignStatementNode.h"
#include "InvalidStatementNode.h"

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

bool IsEndStatementToken(Token& token)
{
    return token.type == TokenType::EndOfLine || token.type == TokenType::Semicolon;
}

StatementNode* Parser::getInvalidToken()
{
    Console::writeline(u"unexpected token '" + current.getSourceText() + u"' at " + current.range.start.toStr());
    while (!IsEndStatementToken(current)) next(false); // panic mode
    next(false);

    return new InvalidStatementNode();
}

StatementNode* Parser::parseStatement()
{
    startToken = &current;

    if (current.type == TokenType::Keyword)
    {
        if (current.getSourceText() == u"var")
        {
            next(false);
            if (current.type == TokenType::Identifier)
            {
                auto node = new VariableNode();
                node->name = current.getSourceText();


                next(false);
                if (IsEndStatementToken(current))
                {
                    next(false);
                    return new VariableDeclarationNode();
                }
            }
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

    return getInvalidToken();
}

void Parser::parseExpression()
{

}

void Parser::match(TokenType type)
{

}


