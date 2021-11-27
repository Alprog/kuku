
#include "Instance.h"
#include "Cell.h"

void Instance::dump()
{
    Cells[0].classPointer->dump(*this);
}