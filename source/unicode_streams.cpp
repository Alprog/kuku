
#include "unicode_streams.h"

namespace unicode {

Utf8to16_stream::Utf8to16_stream(Input_stream<utf8unit>& utf8_stream)
    : utf8_stream{ utf8_stream }
{
}

bool Utf8to16_stream::next(utf16unit& out_character)
{
    if (queue.size() == 0)
    {
        character character = read_utf8(utf8_stream);
        if (character != 0)
        {
            write_utf16(character, queue);
        }
        else
        {
            return false;
        }
    }

    out_character = queue.front();
    queue.pop();
    return true;
}

}