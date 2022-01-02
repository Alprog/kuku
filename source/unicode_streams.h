#pragma once

#include "unicode.h"
#include "streams.h"
#include <queue>

namespace unicode
{
    class Utf8to16_stream : public Input_stream<utf16unit>
    {
    public:
        Input_stream<utf8unit>& utf8_stream;
        std::queue<utf16unit> queue;

        Utf8to16_stream(Input_stream<utf8unit>& utf8_stream);

        virtual bool next(utf16unit& out_character) override;
    };
}
