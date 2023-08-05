
#include "class.h"
#include <iostream>

user_class::user_class(std::string name)
    : name{name}
    , instance_size{1}
{
}

field& user_class::register_field(std::string name, data_type data_type)
{
    return fields.emplace_back(*this, name, data_type, instance_size++);
}

instance user_class::create_instance()
{
    instance instance;
    instance.cells = new cell[instance_size];
    instance.cells[0].class_pointer = this;
    return instance;
}

void user_class::dump(instance instance)
{
    std::cout << sizeof(instance) << std::endl;

    std::cout << instance.cells[0].class_pointer->name << std::endl;
    for (auto& field : fields)
    {
        auto value = instance.cells[field.instance_offset].number;
        std::cout << field.name << " " << value << std::endl;
    }
}