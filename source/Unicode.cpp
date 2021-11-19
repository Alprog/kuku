
#include "Unicode.h"
#include "Cell.h"

constexpr byte HAS_2_OCTETS = 0b11000000;
constexpr byte HAS_3_OCTETS = 0b11100000;
constexpr byte HAS_4_OCTETS = 0b11110000;
constexpr byte CONTINUATION = 0b10000000;

void unicode::writeUTF8(character character, std::vector<byte>& bytes)
{
    if (character < 128) // 7 bit
    {
        bytes.push_back(character);
    }
    else if (character < 2048) // 11 bit
    {
        bytes.push_back((character >> 6) & 0b00011111 | HAS_2_OCTETS); // 5
        bytes.push_back((character >> 0) & 0b00111111 | CONTINUATION); // 6
    }
    else if (character < 65536) // 16 bit
    {
        bytes.push_back((character >> 12) & 0b00001111 | HAS_3_OCTETS); // 4
        bytes.push_back((character >> 06) & 0b00111111 | CONTINUATION); // 6
        bytes.push_back((character >> 00) & 0b00111111 | CONTINUATION); // 6
    }
    else // 21 bit
    {
        bytes.push_back((character >> 18) & 0b00000111 | HAS_4_OCTETS); // 3
        bytes.push_back((character >> 12) & 0b00111111 | CONTINUATION); // 6
        bytes.push_back((character >> 06) & 0b00111111 | CONTINUATION); // 6
        bytes.push_back((character >> 00) & 0b00111111 | CONTINUATION); // 6
    }
}

character unicode::readUTF8(InputStream<byte>& stream)
{
    byte byte;
    stream.next(byte);
    if (byte < 128)
    {
        return byte;
    }

    character character;
    int continuation_count;
    if (byte >= HAS_4_OCTETS)
    {
        character = byte & 0b111; // 3 bits
        continuation_count = 3;
    }
    else if (byte >= HAS_3_OCTETS)
    {
        character = byte & 0b1111; // 4 bits
        continuation_count = 2;
    }
    else if (byte >= HAS_2_OCTETS)
    {
        character = byte & 0b11111; // 5 bits
        continuation_count = 1;
    }
    else
    {
        return 0; // error
    }

    while (continuation_count > 0)
    {
        stream.next(byte);

        if ((byte & 0b11000000) == CONTINUATION)
        {
            character = (character << 6) + (byte & 0b00111111);
            continuation_count--;
            //stream.get();
        }
        else
        {
            return 0; // error
        }
    }

    return character;
}
