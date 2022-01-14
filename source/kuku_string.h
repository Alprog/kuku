#pragma once

#include "types.h"
#include <string>

class String
{
private:
	String(int32_t character_count, byte character_size, void* src_bytes);

public:
	String(std::string u8string);
	String(std::u16string u16string);
	String(std::u32string u32string);

	character get_character(integer index);

	int32_t character_count;
	byte character_size;

	union
	{
		byte* bytes;
		utf16unit* units;
		character* characters;
	};
};