#pragma once

#include "unicode.h"
#include "streams.h"
#include <deque>

namespace unicode
{
    class Utf8to16_stream : public Input_stream<utf16unit>
    {
    public:
        Input_stream<utf8unit>& input_stream;
        Queue_stream<utf16unit> queue_stream;

        Utf8to16_stream(Input_stream<utf8unit>& utf8_stream);

        virtual bool read(utf16unit& out_unit) override;
    };
}
