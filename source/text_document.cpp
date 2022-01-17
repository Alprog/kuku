
#include "text_document.h"

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
        if (unit == '\n')
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
    if (start.line == end.line)
    {
        auto offset = start.character;
        auto size = end.character - start.character;
        lines[start.line].replace(offset, size, event.text.c_str());
    }
    else
    {
        auto deleted_lines_count = end.line - start.line - 1;
        auto line_begin = lines[start.line].substr(0, start.character);
        auto line_end = lines[end.line].substr(start.character);

        lines[start.line] = line_begin + event.text + line_end;
    }
}