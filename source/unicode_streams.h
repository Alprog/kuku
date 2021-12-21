#pragma once

#include "unicode.h"
#include "streams.h"
#include <queue>

namespace unicode
{
    class Utf8To16Stream : public InputStream<utf16unit>
    {
    public:
        InputStream<byte>& utf8stream;
        std::queue<utf16unit> queue;

        Utf8To16Stream(InputStream<byte>& utf8stream);

        virtual bool next(utf16unit& outCharacter) override;
    };
}
