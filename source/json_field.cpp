
#include "json_field.h"
#include "json_serializable.h"

nlohmann::json serialize(Json_serializable& serializable)
{
    return serializable.to_json();
}

int serialize(int value) { return value; }
float serialize(float value) { return value; }
std::string serialize(std::string value) { return value; }
std::u8string serialize(std::u8string value) { return value; }