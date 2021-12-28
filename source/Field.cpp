
#include "field.h"

Field::Field(Class& owner_class, std::string name, Data_type type, int instance_offset)
    : owner_class{ owner_class }
    , name{ name }
    , type{ type }
    , instance_offset{ instance_offset }
{
}