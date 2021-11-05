
#include "TypeRegistry.h"

Class& TypeRegistry::RegisterClass(std::string name)
{
    return Classes.emplace_back(name);
}