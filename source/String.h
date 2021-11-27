#pragma once

#include "types.h"
#include <string>

class String
{
private:
	String(int32_t characterCount, byte characterSize, void* srcBytes);

public:
	String(std::string u8string);
	String(std::u16string u16string);
	String(std::u32string u32string);

	character getCharacter(integer index);

	int32_t characterCount;
	byte characterSize;

	union
	{
		byte* bytes;
		utf16unit* units;
		character* characters;
	};
};