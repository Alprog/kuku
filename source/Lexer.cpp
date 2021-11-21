
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

bool isQuote(utf16unit c)
{
    return c == '"' || c == '\'' || c == '`';
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
            case '\0':
                return createToken(it++, TokenType::EndOfSource);

            case '\n':
                return createToken(it++, TokenType::EndOfLine);

            case ' ':
                ++it;
                continue;

            case '#':
            {
                auto startIt = it++;
                if (*it == '[')
                {
                    it++;
                    return finishMultilineComment(startIt, '#', ']');
                }
                else
                {
                    return finishOneLineComment(startIt);
                }
            }

            case '*':
            {
                auto startIt = it++;
                if (*it == '/')
                {
                    it++;
                    return finishMultilineComment(startIt, '/', '*');
                }
                else
                {
                    return createToken(startIt, TokenType::Operator);
                }
            }

            case '/':
            {
                auto startIt = it++;
                if (*it == '*')
                {
                    return finishOneLineComment(startIt);
                }
                else
                {
                    return createToken(startIt, TokenType::Operator);
                }
            }

            case '+':
            case '=':
                return createToken(it++, TokenType::Operator);

            case ';':
                return createToken(it++, TokenType::Semicolon);

            case '{':
            case '}':
            case '(':
            case ')':
                return createToken(it++, TokenType::Bracket);
        }

        if (isQuote(c))
        {
            auto startIt = it++;
            return finishString(startIt, c, true);
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

            std::u16string id = textDocument.getSubstring({ startIt.position, it.position });
            if (id == u"R" && isQuote(*it))
            {
                return finishString(startIt, *it++, false);
            }
            if (id == u"true" || id == u"false")
            {
                return createToken(startIt, TokenType::BoolLiteral);
            }

            return createToken(startIt, TokenType::UpperCaseIdentifier);
        }

        ++it;
    }
}

Token Lexer::finishOneLineComment(SourceIterator startIt)
{
    while (*it != '\n') ++it;
    return createToken(startIt, TokenType::Comment);
}

Token Lexer::finishMultilineComment(SourceIterator startIt, utf16unit endSymbol1, utf16unit endSymbol2)
{
    while (true)
    {
        if (!moveTo(endSymbol1) || *it++ == endSymbol2)
        {
            return createToken(startIt, TokenType::Comment);
        }
    }
}

Token Lexer::finishString(SourceIterator startIt, utf16unit endQuote, bool escaping)
{
    auto result = escaping ? moveToEscaped(endQuote) : moveTo(endQuote);
    if (result)
    {
        return createToken(startIt, TokenType::StringLiteral);
    }
    else
    {
        return createToken(startIt, TokenType::UnclosedStringLiteral);
    }
}

bool Lexer::moveTo(utf16unit endSymbol)
{
    utf16unit cur = *it;
    while (cur != '\0')
    {
        it++;
        if (cur == endSymbol)
        {            
            return true;
        }
        cur = *it;
    }
    return false;
}

bool Lexer::moveToEscaped(utf16unit endSymbol)
{
    utf16unit cur = *it;
    bool escaping = false;
    while (cur != '\0' && cur != '\n')
    {        
        it++;
        if (escaping)
        {
            escaping = false;
        }
        else if (cur == '\\')
        {
            escaping = true;
        }
        else if (cur == endSymbol)
        {            
            return true;
        }
        cur = *it;
    }
    return false;
}

Token Lexer::createToken(SourceIterator startIt, TokenType type)
{
    return { startIt.position, it.position, type };
}
