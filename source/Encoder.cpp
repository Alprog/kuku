
#include "Encoder.h"
#include "Unicode.h"

Encoder::Encoder(std::vector<byte>& bytes)
    : bytes{bytes}
{

}

bool Encoder::next()
{
    if (position < bytes.size())
    {
        this->character = unicode::readUTF8(bytes, position);
        return true;
    }
    return false;
}