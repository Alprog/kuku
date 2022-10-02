
#include "lexer.h"

#include <map>
#include "console.h"

auto& get_keywords()
{
    static std::map<std::u16string, Token_type> keywords {
        { u"and", Token_type::Keyword_and },
        { u"class", Token_type::Keyword_class },
        { u"do", Token_type::Keyword_do },
        { u"else", Token_type::Keyword_else },
        { u"end", Token_type::Keyword_end },
        { u"for", Token_type::Keyword_for },
        { u"function", Token_type::Keyword_function },
        { u"or", Token_type::Keyword_or },
        { u"return", Token_type::Keyword_return },
        { u"then", Token_type::Keyword_then },
        { u"var", Token_type::Keyword_var },
        { u"while", Token_type::Keyword_while }
    };

    return keywords;
}

Lexer::Lexer(Text_document& text_document)
    : text_document{ text_document }
    , it{ text_document }
{
}

bool is_digit(utf16unit c)
{
    return c >= '0' && c <= '9';
}

bool is_alpha(utf16unit c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool is_alpha_or_digit(wchar_t c)
{
    return is_digit(c) || is_alpha(c);
}

bool is_quote(utf16unit c)
{
    return c == '"' || c == '\'' || c == '`';
}

token* Lexer::get_next_token()
{
    while (true)
    {
        utf16unit c = *it;
        switch (c)
        {
            case '\0':
                return create_token(it++, Token_type::End_of_source);

            case '\n': 
                return create_token(it++, Token_type::End_of_line);

            case ' ':
                ++it;
                continue;

            case '#':
            {
                auto startIt = it++;
                if (match('['))
                {
                    if (match('#'))
                        return create_token(startIt, Token_type::Comment); //:  #[#     disabled comment begin marker
                    else
                        return finish_block_comment(startIt);              //:  #[...   comment begin marker
                }
                else if (match(']'))
                    return create_token(startIt, Token_type::Comment);     //:  #]      comment end marker
                else
                    return finish_line_comment(startIt);                   //:  #...    single line comment
            }

            case '*':
            {
                auto startIt = it++;
                if (match('/'))
                    return finish_binding_block_comment(startIt);                 //:  */...    binding-comment begin marker
                else
                    return create_token(startIt, Token_type::Multiply_Operator);  //:  *        multiply operator
            }

            case '/':
            {
				auto startIt = it++;
				if (match('*'))
					return finish_line_comment(startIt);                        //:  /*...    single line binding-comment
				else
					return create_token(startIt, Token_type::Divide_Operator);  //:  /        divide operator
			}

            case '^': return create_token(it++, Token_type::Exponent_operator);
            case '-': return create_token(it++, Token_type::Minus_operator);
            case '+': return create_token(it++, Token_type::Plus_operator);
            case '=': return create_token(it++, Token_type::Assign_operator);
            case ':': return create_token(it++, Token_type::Colon);
            case ';': return create_token(it++, Token_type::Semicolon);
            case '.': return create_token(it++, Token_type::Dot);
            case ',': return create_token(it++, Token_type::Comma);
            case '[': return create_token(it++, Token_type::Open_bracket);
            case ']': return create_token(it++, Token_type::Close_bracket);
            case '{': return create_token(it++, Token_type::Open_brace);
            case '}': return create_token(it++, Token_type::Close_brace);
            case '<': return create_token(it++, Token_type::Open_chevron);
            case '>': return create_token(it++, Token_type::Close_chevron);
            case '(': return create_token(it++, Token_type::Open_parenthesis);
            case ')': return create_token(it++, Token_type::Close_parenthesis);
		}

		if (is_quote(c))
		{
            auto start_i = it++;
            return finish_string(start_i, c, true);
        }

        if (is_digit(c) || c == '-')
        {
            auto startIt = it++;
            while (is_digit(*it)) ++it;
            if (*it == '.')
            {
                ++it;
                while (is_digit(*it)) ++it;
                return create_token(startIt, Token_type::Number_literal);
            }
            return create_token(startIt, Token_type::Integer_literal);
        }

        if (is_alpha(c))
        {
            auto startIt = it++;
            while (is_alpha_or_digit(*it)) ++it;

            std::u16string id = text_document.get_substring({ startIt.position, it.position });
            if (id == u"R" && is_quote(*it))
            {
                return finish_string(startIt, *it++, false);
            }
            if (id == u"true" || id == u"false")
            {
                return create_token(startIt, Token_type::Bool_literal);
            }

            auto it = get_keywords().find(id);
            if (it != std::end(get_keywords()))
            {
                return create_token(startIt, it->second);
            }

            return create_token(startIt, Token_type::Identifier);
        }

        ++it;
    }
}

token* Lexer::finish_line_comment(Source_iterator start_it)
{
    while (*it != '\n') ++it;
    return create_token(start_it, Token_type::Comment);
}

token* Lexer::finish_block_comment(Source_iterator start_it)
{
    int level = 1;

    while (move_after('#'))
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

    return create_token(start_it, Token_type::Comment);
}

token* Lexer::finish_binding_block_comment(Source_iterator start_it)
{
    while (move_after('/'))
    {
        if (match('*'))
            break;
    }
    return create_token(start_it, Token_type::Comment);
}

token* Lexer::finish_string(Source_iterator start_it, utf16unit end_quote, bool escaping)
{
    auto result = escaping ? move_after_escaped(end_quote) : move_after(end_quote);
    if (result)
    {
        return create_token(start_it, Token_type::String_literal);
    }
    else
    {
        return create_token(start_it, Token_type::Unclosed_string_literal);
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

bool Lexer::move_after(utf16unit end_symbol)
{
    utf16unit cur = *it;
    while (cur != '\0')
    {
        it++;
        if (cur == end_symbol)
        {            
            return true;
        }
        cur = *it;
    }
    return false;
}

bool Lexer::move_after_escaped(utf16unit end_symbol)
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
        else if (cur == end_symbol)
        {            
            return true;
        }
        cur = *it;
    }
    return false;
}

token* Lexer::create_token(Source_iterator start_it, Token_type type)
{
    return new token { type, text_document, start_it.position, it.position };
}
