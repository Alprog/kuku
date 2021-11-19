
#include "Lexer.h"
#include "Console.h"

Lexer::Lexer(TextDocument& textDocument)
    : textDocument{textDocument}
    , it{textDocument}
    , captureStart{0, 0}
    , captureEnd{0, 0}
{
}

bool isDigit(utf16unit c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(utf16unit c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool isAlphaOrDigit(wchar_t c)
{
    return isDigit(c) || isAlpha(c);
}

void Lexer::process()
{
    std::vector<Token> tokens;

    while (true)
    {
        auto token = getNextToken();
        if (token.type == TokenType::EndOfSource)
        {
            break;
        }
        tokens.push_back(token);
    }

    for (auto& token : tokens)
    {
        auto substring = textDocument.getSubstring(token.range);
        Console::writeline(substring);
    }    
}

Token Lexer::getNextToken()
{
    while (true)
    {
        utf16unit c = *it;
        switch (c)
        {
            case ' ':
                ++it;
                continue;

            case '\0':
                return createToken(it++, TokenType::EndOfSource);

            case '\n':
                return createToken(it++, TokenType::EndOfLine);

            case ';':
                return createToken(it++, TokenType::Semicolon);

            case '{':
            case '}':
            case '(':
            case ')':
                return createToken(it++, TokenType::Bracket);

            case '+':
            case '*':
            case '/':
            case '=':
                return createToken(it++, TokenType::Operator);
        }

        if (isDigit(c) || c == '-')
        {
            auto startIt = it++;
            while (isDigit(*it)) ++it;
            if (*it == '.')
            {
                ++it;
                while (isDigit(*it)) ++it;
                return createToken(startIt, TokenType::NumberLiteral);
            }
            return createToken(startIt, TokenType::IntegerLiteral);
        }

        if (isAlpha(c))
        {
            auto startIt = it++;
            while (isAlphaOrDigit(*it)) ++it;
            return createToken(startIt, TokenType::UpperCaseIdentifier);
        }

        ++it;
    }
}

Token Lexer::createToken(SourceIterator startIt, TokenType type)
{
    return { startIt.position, it.position, type };
}
