#pragma once

#include "json.h"
#include <string>
#include "json_serializable.h"

class Base_json_field
{
public:
    Base_json_field(std::string field_name)
        : field_name{ field_name }
    {
    }

    virtual void serialize(void* instance, nlohmann::json& json) = 0;
    virtual void deserialize(nlohmann::json& json, void* instance) = 0;

    std::string field_name;
};

nlohmann::json serialize(Json_serializable& serializable);
int serialize(int value);
float serialize(float value);
std::string serialize(std::string value);
std::u8string serialize(std::u8string value);

template <typename Class_type, typename Field_type>
class Json_field : public Base_json_field
{
public:
    Field_type Class_type::* member;
    
    Json_field(std::string field_name, Field_type Class_type::* member)
        : Base_json_field{ field_name }
        , member{ member }
    {
    }

    virtual void serialize(void* instance, nlohmann::json& json) override
    {
        json[field_name] = ::serialize( static_cast<Class_type*>(instance)->*member );
    }

    virtual void deserialize(nlohmann::json& json, void* instance) override
    {
        static_cast<Class_type*>(instance)->*member = from_json<Field_type>(json[field_name]);
    }
};