
#include "text_document.h"
#include "utils.h"

Text_document::Text_document()
{

}

Text_document::Text_document(Input_stream<utf16unit>& stream)
{
    std::vector<utf16unit> line;

    auto flush_line = [this, &line]()
    {
        lines.push_back({ std::begin(line), std::end(line) });
        line.clear();
    };


    utf16unit unit, prev_unit = 0;
    while (stream.read(unit))
    {
        if (unit == '\r')
        {
            flush_line();
        }
        else if (unit == '\n')
        {
            if (prev_unit != '\r')
            {
                flush_line();
            }
        }
        else
        {
            line.push_back(unit);
        }
        prev_unit = unit;
    }

    flush_line();
}

utf16unit Text_document::get_character(lsp::position position)
{
    if (position.line < lines.size())
    {
        auto& line = lines[position.line];
        if (position.character < line.size())
        {
            return line[position.character];
        }
        else
        {
            return '\n';
        }
    }
    else
    {
        return '\0';
    }
}

std::u16string Text_document::get_substring(lsp::range range)
{
    auto l1 = range.start.line;
    auto l2 = range.start.line;
    if (l1 == l2)
    {
        if (l1 < lines.size())
        {
            auto c1 = range.start.character;
            auto c2 = range.end.character;
            return lines[l1].substr(c1, c2 - c1);
        }
    }

    throw std::exception("not implemented");
}

void Text_document::change_content(lsp::text_document_content_change_event& event)
{
    auto start = event.range.start;
    auto end = event.range.end;

    auto new_lines = split(event.text, u"\r\n"_s);
    if (new_lines.empty())
    {
        new_lines.push_back(u"");
    }
    auto last_index = new_lines.size() - 1;
    new_lines[0] = lines[start.line].substr(0, start.character) + new_lines[0];
    new_lines[last_index] = new_lines[last_index] + lines[end.line].substr(end.character);

    lines.erase(std::begin(lines) + start.line, std::begin(lines) + end.line + 1);
    lines.insert(std::begin(lines) + start.line, std::begin(new_lines), std::end(new_lines));
}