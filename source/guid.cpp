
#include "guid.h"
#include "base64.h"

guid::guid()
	: bytes{ 0 }
{
}

guid::guid(std::string string)
{
	base64::convert_4_characters_to_3_bytes(&string[0], &bytes[0]);
	base64::convert_4_characters_to_3_bytes(&string[4], &bytes[3]);
}

std::string guid::to_string()
{
	std::string string;
	string.resize(8);
	base64::convert_3_bytes_to_4_characters(&bytes[0], &string[0]);
	base64::convert_3_bytes_to_4_characters(&bytes[3], &string[4]);
	return string;
}