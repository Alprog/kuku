
#include "field.h"

Field::Field(Class& ownerClass, std::string name, DataType type, int instanceOffset)
    : OwnerClass{ ownerClass }
    , Name{ name }
    , Type{ type }
    , InstanceOffset{ instanceOffset }
{
}