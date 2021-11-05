
#include "Instance.h"
#include "Cell.h"

void Instance::Dump()
{
    Cells[0].classPointer->Dump(*this);
}