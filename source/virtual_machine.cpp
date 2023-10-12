
#include "virtual_machine.h"

virtual_machine::virtual_machine()
    : object_storage { *this }
{
}

routine& virtual_machine::create_routine(byte* ip)
{
    return routines.emplace_back(*this, ip);
}