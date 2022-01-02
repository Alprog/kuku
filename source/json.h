
#pragma once

#include "nlohmann/json.h"

#include "unicode_streams.h"

namespace nlohmann
{
    template <>
    struct adl_serializer<std::u8string>
    {
        static void to_json(json& j, const std::u8string& value)
        { 
            nlohmann::to_json(j, reinterpret_cast<const std::string&>(value));
        }

        static void from_json(const json& j, std::u8string& value)
        {
            nlohmann::from_json(j, reinterpret_cast<std::string&>(value));
        }
    };

    template <>
    struct adl_serializer<std::u16string>
    {
        static void to_json(json& j, const std::u16string& value)
        {
            std::u8string u8string;

            std::basic_istringstream bs(u8string);
            Basic_input_stream s(bs);
            unicode::Utf8to16_stream us(s);

            nlohmann::to_json(j, u8string);
        }

        static void from_json(const json& j, std::u16string& value)
        {
            std::u8string u8string;
            nlohmann::from_json(j, u8string);
        }
    };
}