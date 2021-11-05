#pragma once

#include "primitives.h"
#include "Instance.h"
#include "Class.h"

union Cell
{
    byte byte;
    integer integer;
    number number;
    Instance instance;
    Class* classPointer;
};