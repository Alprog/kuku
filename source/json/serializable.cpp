
#include "serializable.h"
#include "json/scheme.h"
#include "json/field.h"

json::object json::serializable::to_json()
{
    auto json = json::object::object();

    for (auto field : this->get_json_scheme().fields)
    {
        field->serialize(this, json);
    }

    return json;
}

void json::serializable::read_fields(json::object& object)
{
    for (auto field : this->get_json_scheme().fields)
    {
        field->deserialize(object, this);
    }
}

template<>
int from_json<int>(json::object& object)
{
    if (object.is_number_integer())
    {
        return object.get<int>();
    }
    throw new std::exception("not integer");
}

template<>
float from_json<float>(json::object& object)
{
    if (object.is_number_float())
    {
        return object.get<float>();
    }
    throw new std::exception("not float");
}

template<>
std::string from_json<std::string>(json::object& object)
{
    if (object.is_string())
    {
        return object.get<std::string>();
    }
    throw new std::exception("not string");
}

template<>
std::u8string from_json<std::u8string>(json::object& object)
{
    if (object.is_string())
    {
        return object.get<std::u8string>();
    }
    throw new std::exception("not string");
}

template<>
std::u16string from_json<std::u16string>(json::object& object)
{
    if (object.is_string())
    {
        return object.get<std::u16string>();
    }
    throw new std::exception("not string");
}