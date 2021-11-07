#pragma once

#include <vector>
#include "primitives.h"

class Encoder
{
public:
    Encoder(std::vector<byte>& bytes);
    bool next();

    character character = '\0';
    size_t position = 0;

private:
    std::vector<byte>& bytes;
};