
#include "Scanner.h"
#include "Console.h"

Scanner::Scanner(std::wstring sourceText)
    : sourceText{ sourceText + L'\0' }
    , currentIndex{0}
{
}

bool isDigit(wchar_t c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(wchar_t c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool isAlphaOrDigit(wchar_t c)
{
    return isDigit(c) || isAlpha(c);
}

void Scanner::process()
{
    std::vector<Token> tokens;

    while (true)
    {
        auto token = getNextToken();
        if (token.Type == TokenType::EndOfSource)
        {
            break;
        }
        tokens.push_back(token);
    }

    for (auto& token : tokens)
    {
        std::wstring result = sourceText.substr(token.Start, token.Length);
        Console::writeline(result);
    }    
}

Token Scanner::getNextToken()
{
    while (true)
    {
        wchar_t c = sourceText[currentIndex++];
        switch (c)
        {
        case ' ':
            continue;

        case '\0':
            return createToken(TokenType::EndOfSource);

        case '\n':
            return createToken(TokenType::EndOfLine);

        case ';':
            return createToken(TokenType::Semicolon);

        case '{':
        case '}':
        case '(':
        case ')':
            return createToken(TokenType::Bracket);

        case '+':
        case '*':
        case '/':
        case '=':
            return createToken(TokenType::Operator);
        }

        if (isDigit(c) || c == '-')
        {
            int startIndex = currentIndex - 1;
            while (isDigit(sourceText[currentIndex])) currentIndex++;
            if (sourceText[currentIndex] == '.')
            {
                currentIndex++;
                while (isDigit(sourceText[currentIndex])) currentIndex++;
                return createToken(TokenType::NumberLiteral, currentIndex - startIndex);
            }
            return createToken(TokenType::IntegerLiteral, currentIndex - startIndex);
        }

        if (isAlpha(c))
        {
            int startIndex = currentIndex - 1;
            while (isAlphaOrDigit(sourceText[currentIndex])) currentIndex++;
            return createToken(TokenType::UpperCaseIdentifier, currentIndex - startIndex);
        }
    }
}

Token Scanner::createToken(TokenType type, int length)
{
    return { currentIndex - length, length, type };
}
