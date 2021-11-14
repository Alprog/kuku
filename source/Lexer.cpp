
#include "Lexer.h"
#include "Console.h"

Lexer::Lexer(TextDocument& textDocument)
    : textDocument{textDocument}
    , sourceIterator{textDocument}
    , captureStart{0, 0}
    , captureEnd{0, 0}
{
}

bool isDigit(uint16_t c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(uint16_t c)
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
        Console::writeline(std::to_wstring(token.range.start.line) + L' ' + std::to_wstring(token.range.start.character) + L' ' +
                           std::to_wstring(token.range.end.line) + L' ' + std::to_wstring(token.range.end.character));
    }    
}

Token Lexer::getNextToken()
{
    while (true)
    {
        uint16_t c = *sourceIterator;
        switch (c)
        {
            case ' ':
                sourceIterator.next();
                continue;

            case '\0':
                return createSingleToken(TokenType::EndOfSource);

            case '\n':
                return createSingleToken(TokenType::EndOfLine);

            case ';':
                return createSingleToken(TokenType::Semicolon);

            case '{':
            case '}':
            case '(':
            case ')':
                return createSingleToken(TokenType::Bracket);

            case '+':
            case '*':
            case '/':
            case '=':
                return createSingleToken(TokenType::Operator);
        }

        if (isDigit(c) || c == '-')
        {
            auto start = sourceIterator.position;
            sourceIterator.next();
            while (isDigit(*sourceIterator)) sourceIterator.next();
            if (*sourceIterator == '.')
            {
                sourceIterator.next();
                while (isDigit(*sourceIterator)) sourceIterator.next();
                return createToken(start, TokenType::NumberLiteral);
            }
            return createToken(start, TokenType::IntegerLiteral);
        }

        if (isAlpha(c))
        {
            auto start = sourceIterator.position;
            sourceIterator.next();
            while (isAlphaOrDigit(*sourceIterator)) sourceIterator.next();
            return createToken(start, TokenType::UpperCaseIdentifier);
        }
    }
}

Token Lexer::createSingleToken(TokenType type)
{
    auto start = sourceIterator.position;
    sourceIterator.next();
    return { start, sourceIterator.position, type };
}

Token Lexer::createToken(Position startPosition, TokenType type)
{
    return { startPosition, sourceIterator.position, type };
}
