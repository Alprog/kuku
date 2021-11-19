
#include "UnicodeStreams.h"

namespace unicode {

Utf8To16Stream::Utf8To16Stream(InputStream<byte>& utf8stream)
    : utf8stream{ utf8stream }
{
}

bool Utf8To16Stream::next(utf16unit& outCharacter)
{
    if (queue.size() == 0)
    {
        character character = readUTF8(utf8stream);
        if (character != 0)
        {
            writeUTF16(character, queue);
        }
        else
        {
            return false;
        }
    }

    outCharacter = queue.front();
    queue.pop();
    return true;
}

}