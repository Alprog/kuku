
#include "bytecode.h"

byte* bytecode::get_start_pointer()
{
	return &bytes[0];
}

byte* bytecode::get_end_pointer()
{
	return &bytes[bytes.size()];
}