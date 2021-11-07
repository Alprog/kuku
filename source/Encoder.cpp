
#include "Encoder.h"
#include "Unicode.h"

Encoder::Encoder(std::vector<byte>& bytes, Encoding encoding)
    : bytes{bytes}
{
    switch (encoding)
    {
        case Encoding::Byte8:
        default:
            next_handler = &Encoder::next_byte8;
            break;

        case Encoding::Byte16:
            next_handler = &Encoder::next_byte16;
            break;
        case Encoding::UTF8:
            next_handler = &Encoder::next_utf8;
            break;
    }    
}

bool Encoder::next()
{
    return (this->*next_handler)();
}

bool Encoder::next_byte8()
{
    if (position < bytes.size())
    {
        this->character = bytes[position++];
        return true;
    }
    return false;
}

bool Encoder::next_byte16()
{
    if (position + 1 < bytes.size())
    {
        this->character = *reinterpret_cast<uint16_t*>(&bytes[position]);
        position += 2;
        return true;
    }
    return false;
}

bool Encoder::next_utf8()
{
    if (position < bytes.size())
    {
        this->character = unicode::readUTF8(bytes, position);
        return true;
    }
    return false;
}