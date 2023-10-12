#pragma once

#include "stack.h"
#include "cell.h"
#include "type_registry.h"
#include "data_type.h"
#include "instance.h"
#include "object_storage.h"
#include "routine.h"

class virtual_machine
{
public:
    explicit virtual_machine();

    type_registry type_registry;
    object_storage object_storage;
    std::vector<routine> routines;

    routine& create_routine(byte* ip);
};