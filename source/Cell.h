#pragma once

#include "types.h"
#include "Instance.h"
#include "Class.h"
#include "String.h"

union Cell
{
    byte byte;
    integer integer;
    number number;
    Instance instance;
    String* string;
    Class* classPointer;
};