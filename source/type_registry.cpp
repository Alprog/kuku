
#include "type_registry.h"

Class& Type_registry::register_class(std::string name)
{
    return Classes.emplace_back(name);
}