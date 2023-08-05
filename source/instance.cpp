
#include "instance.h"
#include "cell.h"

void instance::dump()
{
    cells[0].class_pointer->dump(*this);
}