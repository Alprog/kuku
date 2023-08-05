
#include "class.h"
#include <iostream>

Class::Class(std::string name)
    : name{name}
    , instance_size{1}
{
}

field& Class::register_field(std::string name, data_type data_type)
{
    return fields.emplace_back(*this, name, data_type, instance_size++);
}

Instance Class::create_instance()
{
    Instance instance;
    instance.cells = new cell[instance_size];
    instance.cells[0].class_pointer = this;
    return instance;
}

void Class::dump(Instance instance)
{
    std::cout << sizeof(instance) << std::endl;

    std::cout << instance.cells[0].class_pointer->name << std::endl;
    for (auto& field : fields)
    {
        auto value = instance.cells[field.instance_offset].number;
        std::cout << field.name << " " << value << std::endl;
    }
}