
#pragma once

#include "types.h"
#include <vector>

class Chunk
{
public:
	std::vector<byte> bytes;

	byte* getStartPointer();

	template<typename T>
	void write(T value)
	{
		int end = bytes.size();
		bytes.resize(end + sizeof(T));
		memcpy(&bytes[end], &value, sizeof(T));
	}
};