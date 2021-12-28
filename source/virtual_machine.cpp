
#include "virtual_machine.h"

void Virtual_machine::test()
{
    auto vectorClass = TypeRegistry.RegisterClass("Vector");
    vectorClass.registerField("X", DataType::Number);
    vectorClass.registerField("Y", DataType::Number);
    vectorClass.registerField("Z", DataType::Number);

    auto vectorInstance = vectorClass.createInstance();

    Cell cell;
    cell.number = 41;

    setField(vectorInstance, 2, cell);
    vectorInstance.dump();
}

void Virtual_machine::setLocal(int cellIndex, Cell cellValue)
{
    Stack.Cells[cellIndex] = cellValue;
}

void Virtual_machine::setField(Instance instance, int cellIndex, Cell cellValue)
{
    instance.Cells[cellIndex] = cellValue;
}