
#include <vector>
#include "json/field.h"
#include "json/serializable.h"

namespace json
{
	json::object serialize(json::serializable& serializable)
	{
		return serializable.to_json();
	}

	int serialize(int value) { return value; }
	float serialize(float value) { return value; }
	std::string serialize(std::string value) { return value; }
	std::u8string serialize(std::u8string value) { return value; }
	std::u16string serialize(std::u16string value) { return value; }
}