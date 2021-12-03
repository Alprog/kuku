
#include "Parser.h"
#include "Console.h"
#include "VariableNode.h"
#include "BinaryOperatorNode.h"

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
        parseStatement();
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

void Parser::unexpected()
{
    Console::writeline(u"unexpected token '" + current.getSourceText() + u"' at " + current.range.start.toStr());
    while (current.type != TokenType::EndOfLine) next(false); // panic mode
    next(false);
}

void Parser::parseStatement()
{
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
                if (current.type == TokenType::EndOfLine)
                {
                    next(false);
                    return;
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
                    return;
                }
            }

        }
    }

    unexpected();
}

void Parser::parseExpression()
{

}

void Parser::match(TokenType type)
{

}


