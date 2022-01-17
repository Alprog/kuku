#pragma once

#include <string>
#include "json/object.h"
#include "json/serializable.h"

namespace json
{
    class base_field
    {
    public:
        base_field(std::string field_name)
            : field_name{ field_name }
        {
        }

        virtual void serialize(void* instance, json::object& object) = 0;
        virtual void deserialize(json::object& object, void* instance) = 0;

        std::string field_name;
    };

    json::object serialize(json::serializable& serializable);
    int serialize(int value);
    float serialize(float value);
    std::string serialize(std::string value);
    std::u8string serialize(std::u8string value);
    std::u16string serialize(std::u16string value);

    template <typename T>
    json::object serialize(std::vector<T> vector)
    {
        auto result = json::object::array();
        for (int i = 0; i < vector.size(); i++)
        {
            result[i] = json::serialize(vector[i]);
        }
        return json::object();
    }

    template <typename Class_type, typename Field_type>
    class field : public base_field
    {
    public:
        Field_type Class_type::* member;

        field(std::string field_name, Field_type Class_type::* member)
            : base_field{ field_name }
            , member{ member }
        {
        }

        virtual void serialize(void* instance, json::object& object) override
        {
            object[field_name] = json::serialize(static_cast<Class_type*>(instance)->*member);
        }

        virtual void deserialize(json::object& object, void* instance) override
        {
            static_cast<Class_type*>(instance)->*member = from_json<Field_type>(object[field_name]);
        }
    };
}

