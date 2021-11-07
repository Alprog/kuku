#pragma once

#include <vector>
#include "primitives.h"
#include "Encoding.h"

class Encoder
{
public:
    Encoder(std::vector<byte>& bytes, Encoding encoding);
    bool next();

    character character = '\0';
    size_t position = 0;
    
private:
    bool next_byte8();
    bool next_byte16();
    bool next_utf8();

    std::vector<byte>& bytes;
    bool (Encoder::* next_handler)();
};