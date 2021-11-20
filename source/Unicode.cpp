
#include "Unicode.h"
#include "Cell.h"

constexpr int COUNT_7_BIT = 128;
constexpr int COUNT_11_BIT = 2048;
constexpr int COUNT_16_BIT = 65536;

constexpr byte HAS_2_OCTETS = 0b11000000;
constexpr byte HAS_3_OCTETS = 0b11100000;
constexpr byte HAS_4_OCTETS = 0b11110000;
constexpr byte CONTINUATION = 0b10000000;

void unicode::writeUTF8(character character, std::vector<byte>& bytes)
{
    if (character < COUNT_7_BIT)
    {
        bytes.push_back(character);
    }
    else if (character < COUNT_11_BIT)
    {
        bytes.push_back((character >> 6) & 0b00011111 | HAS_2_OCTETS); // 5
        bytes.push_back((character >> 0) & 0b00111111 | CONTINUATION); // 6
    }
    else if (character < COUNT_16_BIT)
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

constexpr utf16unit SURROGATES_START = 0xD800;
constexpr utf16unit SURROGATES_HALF = 0xDC00;
constexpr utf16unit SURROGATES_END = 0xE000;

void unicode::writeUTF16(character character, std::queue<utf16unit>& units)
{
    if (character < COUNT_16_BIT)
    {
        if (character >= SURROGATES_START && character < SURROGATES_END)
        {
            throw std::exception("can't write surrogate pair as utf-16");
        }
        else
        {
            units.push(character);
        }
    }
    else
    {
        auto remainder = character - COUNT_16_BIT; // 20-bit remainder
        auto w1 = SURROGATES_START + (remainder >> 10);         // high 10 bits
        auto w2 = SURROGATES_HALF + (remainder & 0b1111111111); // low 10 bits
        units.push(w1);
        units.push(w2);
    }
}

character unicode::readUTF16(InputStream<utf16unit>& stream)
{
    utf16unit firstUnit;
    stream.next(firstUnit);

    if (firstUnit < SURROGATES_START || firstUnit >= SURROGATES_END)
    {
        return firstUnit;
    }

    utf16unit secondUnit;
    stream.next(secondUnit);

    auto highBits = (character)(firstUnit - SURROGATES_START) << 10;
    auto lowBits = (character)(secondUnit - SURROGATES_END);
    return highBits + lowBits + COUNT_16_BIT;    
}