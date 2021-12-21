
#include "instance.h"
#include "cell.h"

void Instance::dump()
{
    Cells[0].classPointer->dump(*this);
}