
#include "Lexer.h"
#include "Console.h"

std::vector<std::u16string> keywords { 
    u"function", 
    u"end",
    u"while",
    u"else",
    u"for",
    u"and",
    u"or",
    u"then",
    u"do",
    u"var"
};

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
                if (match('['))
                {
                    if (match('#'))
                        return createToken(startIt, TokenType::Comment); //:  #[#     disabled comment begin marker
                    else
                        return finishBlockComment(startIt);              //:  #[...   comment begin marker
                }
                else if (match(']'))
                    return createToken(startIt, TokenType::Comment);     //:  #]      comment end marker
                else
                    return finishLineComment(startIt);                   //:  #...    single line comment
            }

            case '*':
            {
                auto startIt = it++;
                if (match('/'))
                    return finishBindingBlockComment(startIt);         //:  */...    binding-comment begin marker
                else
                    return createToken(startIt, TokenType::Operator);  //:  *        multiply operator
            }

            case '/':
            {
                auto startIt = it++;
                if (match('*'))
                    return finishLineComment(startIt);                 //:  /*...    single line binding-comment
                else
                    return createToken(startIt, TokenType::Operator);  //:  /        divide operator
            }

            case '+':
                return createToken(it++, TokenType::PlusSign);

            case '=':
                return createToken(it++, TokenType::AssignOperator);

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
            if (std::find(std::begin(keywords), std::end(keywords), id) != std::end(keywords))
            {
                return  createToken(startIt, TokenType::Keyword);
            }

            return createToken(startIt, TokenType::Identifier);
        }

        ++it;
    }
}

Token Lexer::finishLineComment(SourceIterator startIt)
{
    while (*it != '\n') ++it;
    return createToken(startIt, TokenType::Comment);
}

Token Lexer::finishBlockComment(SourceIterator startIt)
{
    int level = 1;

    while (moveAfter('#'))
    {
        if (match('['))
        {
            level++;
        }
        else if (match(']'))
        {
            if (--level == 0)
                break;
        }
    }

    return createToken(startIt, TokenType::Comment);
}

Token Lexer::finishBindingBlockComment(SourceIterator startIt)
{
    while (moveAfter('/'))
    {
        if (match('*'))
            break;
    }
    return createToken(startIt, TokenType::Comment);
}

Token Lexer::finishString(SourceIterator startIt, utf16unit endQuote, bool escaping)
{
    auto result = escaping ? moveAfterEscaped(endQuote) : moveAfter(endQuote);
    if (result)
    {
        return createToken(startIt, TokenType::StringLiteral);
    }
    else
    {
        return createToken(startIt, TokenType::UnclosedStringLiteral);
    }
}

// check current symbol and step forward if it match
bool Lexer::match(utf16unit symbol)
{
    if (*it == symbol)
    {
        ++it;
        return true;
    }
    return false;
}

bool Lexer::moveAfter(utf16unit endSymbol)
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

bool Lexer::moveAfterEscaped(utf16unit endSymbol)
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
    return { type, &textDocument, startIt.position, it.position };
}
