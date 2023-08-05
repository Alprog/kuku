
#include "virtual_machine.h"

void Virtual_machine::test()
{
    auto vector_class = Type_registry.register_class("Vector");
    vector_class.register_field("X", data_type::Number);
    vector_class.register_field("Y", data_type::Number);
    vector_class.register_field("Z", data_type::Number);

    auto vector_instance = vector_class.create_instance();

    cell cell;
    cell.number = 41;

    set_field(vector_instance, 2, cell);
    vector_instance.dump();
}

void Virtual_machine::set_local(int cellIndex, cell cellValue)
{
    stack.cells[cellIndex] = cellValue;
}

void Virtual_machine::set_field(instance instance, int cellIndex, cell cellValue)
{
    instance.cells[cellIndex] = cellValue;
}