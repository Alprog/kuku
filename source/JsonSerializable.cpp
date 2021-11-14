
#include "JsonSerializable.h"
#include "JsonScheme.h"
#include "JsonField.h"

nlohmann::json JsonSerializable::toJson()
{
    auto json = nlohmann::json::object();

    for (auto field : this->GetJsonScheme().fields)
    {
        field->serialize(this, json);
    }

    return json;
}

void JsonSerializable::readFields(nlohmann::json& json)
{
    for (auto field : this->GetJsonScheme().fields)
    {
        field->deserialize(json, this);
    }
}

template<>
int fromJson<int>(nlohmann::json& json)
{
    if (json.is_number_integer())
    {
        return json.get<int>();
    }
    throw new std::exception("not integer");
}

template<>
float fromJson<float>(nlohmann::json& json)
{
    if (json.is_number_float())
    {
        return json.get<float>();
    }
    throw new std::exception("not float");
}

template<>
std::string fromJson<std::string>(nlohmann::json& json)
{
    if (json.is_string())
    {
        return json.get<std::string>();
    }
    throw new std::exception("not string");
}