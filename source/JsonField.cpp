
#include "JsonField.h"
#include "JsonSerializable.h"

nlohmann::json serialize(JsonSerializable& serializable)
{
    return serializable.toJson();
}

int serialize(int value) { return value; }
float serialize(float value) { return value; }
std::string serialize(std::string value) { return value; }
