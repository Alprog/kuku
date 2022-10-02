#pragma once

#include "types.h"
#include "instance.h"
#include "class.h"
#include "kuku/string.h"

union Cell
{
    byte byte;
    integer integer;
    number number;
    Instance instance;
    kuku::string* string;
    Class* class_pointer;
};