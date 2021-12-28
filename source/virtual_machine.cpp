
#include "virtual_machine.h"

void Virtual_machine::test()
{
    auto vector_class = Type_registry.register_class("Vector");
    vector_class.register_field("X", Data_type::Number);
    vector_class.register_field("Y", Data_type::Number);
    vector_class.register_field("Z", Data_type::Number);

    auto vector_instance = vector_class.create_instance();

    Cell cell;
    cell.number = 41;

    set_field(vector_instance, 2, cell);
    vector_instance.dump();
}

void Virtual_machine::set_local(int cellIndex, Cell cellValue)
{
    stack.cells[cellIndex] = cellValue;
}

void Virtual_machine::set_field(Instance instance, int cellIndex, Cell cellValue)
{
    instance.cells[cellIndex] = cellValue;
}