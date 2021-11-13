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

    virtual void write(nlohmann::json& json, void* instance) = 0;

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

    virtual void write(nlohmann::json& json, void* instance) override
    {
        json[fieldName] = static_cast<ClassType*>(instance)->*member;
    }

    void set(ClassType& instance, FieldType& value)
    {
        instance.*member = value;
    }

    FieldType& get(ClassType& instance)
    {
        return instance.*member;
    }

    void tryRead(nlohmann::json& json)
    {
        json[fieldName].is_number();
    }

    void write(nlohmann::json& json)
    {
        json[fieldName] = 3;
    }
};