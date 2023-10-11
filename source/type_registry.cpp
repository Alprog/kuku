#include "type_registry.h"

rt::user_class& type_registry::register_class(std::string name)
{
    return classes.emplace_back(name);
}