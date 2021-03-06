#pragma once

#include "types.h"
#include "instance.h"
#include "class.h"
#include "kuku_string.h"

union Cell
{
    byte byte;
    integer integer;
    number number;
    Instance instance;
    String* string;
    Class* class_pointer;
};