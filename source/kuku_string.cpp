
#include "kuku_string.h"

String::String(int32_t character_count, byte character_size, void* src_bytes)
	: character_count{ character_count }
	, character_size{ character_size }
{
	auto size = character_count * character_size;
	bytes = new byte[size];
	memcpy(bytes, src_bytes, size);
}

String::String(std::string u8string)
	: String{ (byte)u8string.size(), 1, &u8string[0] }
{
}

String::String(std::u16string u16string)
	: String{ u16string.size(), 2, &u16string[0] }
{
}

String::String(std::u32string u32string)
	: String{ u32string.size(), 4, &u32string[0] }
{
}

String::~String()
{
	delete[] bytes;
}

character String::get_character(integer index)
{
	switch (character_size)
	{
		default:
		case 1:
			return bytes[index];
		case 2:
			return units[index];
		case 4:
			return characters[index];
	}
}