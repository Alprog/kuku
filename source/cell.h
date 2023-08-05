#pragma once

#include "types.h"
#include "instance.h"
#include "class.h"
#include "kuku/string.h"

union cell
{
    byte byte;
    integer integer;
    number number;
    instance instance;
    kuku::string* string;
    Class* class_pointer;
};