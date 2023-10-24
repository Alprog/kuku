
#pragma once

#include "types.h"
#include <vector>

class bytecode
{
public:
	std::vector<byte> bytes;

	byte* get_start_pointer();
	byte* get_end_pointer();
	
	template<typename T>
	void write(T value)
	{
		int end = bytes.size();
		bytes.resize(end + sizeof(T));
		memcpy(&bytes[end], &value, sizeof(T));
	}
};