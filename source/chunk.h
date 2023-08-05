
#pragma once

#include "types.h"
#include <vector>

class chunk
{
public:
	std::vector<byte> bytes;

	byte* get_start_pointer();

	template<typename T>
	void write(T value)
	{
		int end = bytes.size();
		bytes.resize(end + sizeof(T));
		memcpy(&bytes[end], &value, sizeof(T));
	}
};