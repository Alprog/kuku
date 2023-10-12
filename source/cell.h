#pragma once

#include "types.h"
#include "instance.h"
#include "rt/user_class.h"
#include "kuku/string.h"

union cell
{
    byte byte;
    integer integer;
    number number;
    object_index object_index;
    kuku::string* string;
    rt::user_class* class_pointer;
};