
#include "json_serializable.h"
#include "json_scheme.h"
#include "json_field.h"

nlohmann::json Json_serializable::to_json()
{
    auto json = nlohmann::json::object();

    for (auto field : this->get_json_scheme().fields)
    {
        field->serialize(this, json);
    }

    return json;
}

void Json_serializable::read_fields(nlohmann::json& json)
{
    for (auto field : this->get_json_scheme().fields)
    {
        field->deserialize(json, this);
    }
}

template<>
int from_json<int>(nlohmann::json& json)
{
    if (json.is_number_integer())
    {
        return json.get<int>();
    }
    throw new std::exception("not integer");
}

template<>
float from_json<float>(nlohmann::json& json)
{
    if (json.is_number_float())
    {
        return json.get<float>();
    }
    throw new std::exception("not float");
}

template<>
std::string from_json<std::string>(nlohmann::json& json)
{
    if (json.is_string())
    {
        return json.get<std::string>();
    }
    throw new std::exception("not string");
}

template<>
std::u8string from_json<std::u8string>(nlohmann::json& json)
{
    if (json.is_string())
    {
        return json.get<std::u8string>();
    }
    throw new std::exception("not string");
}