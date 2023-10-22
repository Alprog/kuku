
#include "lexer.h"

#include <map>
#include "console.h"

auto& get_keywords()
{
    static std::map<std::u16string, token_type> keywords {
        { u"and", token_type::Keyword_and },
        { u"class", token_type::Keyword_class },
        { u"do", token_type::Keyword_do },
        { u"else", token_type::Keyword_else },
        { u"end", token_type::Keyword_end },
        { u"for", token_type::Keyword_for },
        { u"function", token_type::Keyword_function },
        { u"if", token_type::Keyword_if },
        { u"or", token_type::Keyword_or },
        { u"return", token_type::Keyword_return },
        { u"then", token_type::Keyword_then },
        { u"var", token_type::Keyword_var },
        { u"while", token_type::Keyword_while }
    };

    return keywords;
}

lexer::lexer(::text_document& text_document)
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

token* lexer::get_next_token()
{
    while (true)
    {
        utf16unit c = *it;
        switch (c)
        {
            case '\0':
                return create_token(it++, token_type::End_of_source);

            case '\n': 
                return create_token(it++, token_type::End_of_line);

            case ' ':
                ++it;
                continue;

            case '#':
            {
                auto startIt = it++;
                if (match('['))
                {
                    if (match('#'))
                        return create_token(startIt, token_type::Comment); //:  #[#     disabled comment begin marker
                    else
                        return finish_block_comment(startIt);              //:  #[...   comment begin marker
                }
                else if (match(']'))
                    return create_token(startIt, token_type::Comment);     //:  #]      comment end marker
                else
                    return finish_line_comment(startIt);                   //:  #...    single line comment
            }

            case '*':
            {
                auto startIt = it++;
                if (match('/'))
                    return finish_binding_block_comment(startIt);                 //:  */...    binding-comment begin marker
                else
                    return create_token(startIt, token_type::Multiply_Operator);  //:  *        multiply operator
            }

            case '/':
            {
				auto startIt = it++;
				if (match('*'))
					return finish_line_comment(startIt);                        //:  /*...    single line binding-comment
				else
					return create_token(startIt, token_type::Divide_Operator);  //:  /        divide operator
			}

            case '=':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::Equal_operator);   //: ==
                else
                    return create_token(startIt, token_type::Assign_operator);  //: =
            }

            case '<':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::Less_or_equal_operator);  //: <=
                else
                    return create_token(startIt, token_type::Less_operator);           //: <
            }

            case '>':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::Greater_or_equal_operator);  //: >=
                else
                    return create_token(startIt, token_type::Greater_operator);           //: >
            }

            case '!':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::Not_equal_operator); //: !=
                else
                    return create_token(startIt, token_type::Not_operator);       //: !
            }

            case '^': return create_token(it++, token_type::Exponent_operator);
            case '-': return create_token(it++, token_type::Minus_operator);
            case '+': return create_token(it++, token_type::Plus_operator);            
            case ':': return create_token(it++, token_type::Colon);
            case ';': return create_token(it++, token_type::Semicolon);
            case '.': return create_token(it++, token_type::Dot);
            case ',': return create_token(it++, token_type::Comma);
            case '[': return create_token(it++, token_type::Open_bracket);
            case ']': return create_token(it++, token_type::Close_bracket);
            case '{': return create_token(it++, token_type::Open_brace);
            case '}': return create_token(it++, token_type::Close_brace);
            case '(': return create_token(it++, token_type::Open_parenthesis);
            case ')': return create_token(it++, token_type::Close_parenthesis);
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
                return create_token(startIt, token_type::Number_literal);
            }
            return create_token(startIt, token_type::Integer_literal);
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
                return create_token(startIt, token_type::Bool_literal);
            }

            auto it = get_keywords().find(id);
            if (it != std::end(get_keywords()))
            {
                return create_token(startIt, it->second);
            }

            return create_token(startIt, token_type::Identifier);
        }

        ++it;
    }
}

token* lexer::finish_line_comment(source_iterator start_it)
{
    while (*it != '\n') ++it;
    return create_token(start_it, token_type::Comment);
}

token* lexer::finish_block_comment(source_iterator start_it)
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

    return create_token(start_it, token_type::Comment);
}

token* lexer::finish_binding_block_comment(source_iterator start_it)
{
    while (move_after('/'))
    {
        if (match('*'))
            break;
    }
    return create_token(start_it, token_type::Comment);
}

token* lexer::finish_string(source_iterator start_it, utf16unit end_quote, bool escaping)
{
    auto result = escaping ? move_after_escaped(end_quote) : move_after(end_quote);
    if (result)
    {
        return create_token(start_it, token_type::String_literal);
    }
    else
    {
        return create_token(start_it, token_type::Unclosed_string_literal);
    }
}

// check current symbol and step forward if it match
bool lexer::match(utf16unit symbol)
{
    if (*it == symbol)
    {
        ++it;
        return true;
    }
    return false;
}

bool lexer::move_after(utf16unit end_symbol)
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

bool lexer::move_after_escaped(utf16unit end_symbol)
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

token* lexer::create_token(source_iterator start_it, token_type type)
{
    return new token { type, text_document, start_it.position, it.position };
}
