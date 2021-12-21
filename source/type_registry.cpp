
#include "type_registry.h"

Class& TypeRegistry::RegisterClass(std::string name)
{
    return Classes.emplace_back(name);
}