
#include "instance.h"
#include "cell.h"

void Instance::dump()
{
    cells[0].class_pointer->dump(*this);
}