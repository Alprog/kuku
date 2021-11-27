
#include "Class.h"
#include <iostream>

Class::Class(std::string name)
    : Name{name}
    , InstanceSize{1}
{
}

Field& Class::registerField(std::string name, DataType dataType)
{
    return Fields.emplace_back(*this, name, dataType, InstanceSize++);
}

Instance Class::createInstance()
{
    Instance instance;
    instance.Cells = new Cell[InstanceSize];
    instance.Cells[0].classPointer = this;
    return instance;
}

void Class::dump(Instance instance)
{
    std::cout << sizeof(instance) << std::endl;

    std::cout << instance.Cells[0].classPointer->Name << std::endl;
    for (auto& field : Fields)
    {
        auto value = instance.Cells[field.InstanceOffset].number;
        std::cout << field.Name << " " << value << std::endl;
    }
}