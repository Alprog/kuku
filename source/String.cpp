
#include "string.h"

String::String(int32_t characterCount, byte characterSize, void* srcBytes)
	: characterCount{ characterCount }
	, characterSize{ characterSize }
{
	auto size = characterCount * characterSize;
	bytes = new byte[size];
	memcpy(bytes, srcBytes, size);
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

character String::getCharacter(integer index)
{
	switch (characterSize)
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