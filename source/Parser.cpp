
#include "Parser.h"
#include "Console.h"

Parser::Parser(Lexer& lexer)
	: lexer{ lexer }
{

}

void Parser::process()
{
    auto token = getNextToken();
    if (token.type == TokenType::Keyword)
    {
        Console::writeline(u"keyword");
    }
    else
    {
        Console::writeline(u"unexpected");
    }
}

Token Parser::getNextToken()
{
    auto token = lexer.getNextToken();
    if (token.type == TokenType::Comment)
    {
        return getNextToken();
    }
    return token;
}