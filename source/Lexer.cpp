
#include "Lexer.h"
#include "Console.h"

Lexer::Lexer(std::vector<byte>& bytes)
    : encoder{bytes, Encoding::UTF8}
    , bytes{bytes}
    , captureStart{0}
    , captureEnd{0}
{
}

bool isDigit(character c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(character c)
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
        if (token.Type == TokenType::EndOfSource)
        {
            break;
        }
        tokens.push_back(token);
    }

    //for (auto& token : tokens)
    {
        //bytes.

        //std::string result = sourceText.substr(token.Start, token.Length);
        //Console::writeline(result);
    }    
}

Token Lexer::getNextToken()
{
    while (encoder.next())
    {
        character c = encoder.character;
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
            captureCharacter();
            while (isDigit(encoder.character)) captureCharacter();
            if (encoder.character == '.')
            {
                captureCharacter();
                while (isDigit(encoder.character)) captureCharacter();
                return createToken(TokenType::NumberLiteral);
            }
            return createToken(TokenType::IntegerLiteral);
        }

        if (isAlpha(c))
        {
            captureCharacter();
            while (isAlphaOrDigit(encoder.character)) captureCharacter();
            return createToken(TokenType::UpperCaseIdentifier);
        }
    }

    return Token(0, 0, TokenType::EndOfSource);
}

void Lexer::omitCharacter()
{
    captureStart = encoder.character;
    captureEnd = encoder.character;
}

void Lexer::captureCharacter()
{
    captureEnd = encoder.position;
    encoder.next();
}

Token Lexer::createToken(TokenType type)
{
    return { captureStart, captureEnd - captureStart, type };
}
