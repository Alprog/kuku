#pragma once

#include "json.h"
#include <string>

class BaseJsonField
{
public:
    BaseJsonField(std::string fieldName)
        : fieldName{ fieldName }
    {
    }

    virtual void serialize(void* instance, nlohmann::json& json) = 0;
    virtual void deserialize(nlohmann::json& json, void* instance) = 0;

    std::string fieldName;
};

template <typename ClassType, typename FieldType>
class JsonField : public BaseJsonField
{
public:
    FieldType ClassType::* member;
    
    JsonField(std::string fieldName, FieldType ClassType::* member)
        : BaseJsonField{ fieldName }
        , member{ member }
    {
    }

    virtual void serialize(void* instance, nlohmann::json& json) override
    {
        json[fieldName] = static_cast<ClassType*>(instance)->*member;
    }

    virtual void deserialize(nlohmann::json& json, void* instance) override
    {
        static_cast<ClassType*>(instance)->*member = json[fieldName].get<unsigned int>();
    }
};