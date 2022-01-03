
#include "unicode_streams.h"

namespace unicode {

Utf8to16_stream::Utf8to16_stream(Input_stream<utf8unit>& input_stream)
    : input_stream{ input_stream }
{
}

bool Utf8to16_stream::read(utf16unit& out_unit)
{
    if (queue_stream.read(out_unit))
    {
        return true;
    }

    character character;
    if (read_character(input_stream, character))
    {
        write_character(queue_stream, character);
        if (queue_stream.read(out_unit))
        {
            return true;
        }
    }
    
    return false;
}

}