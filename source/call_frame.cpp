#include "call_frame.h"

call_frame::call_frame(rt::function& function, cell* stack)
	: function { &function }
	, stack { stack }
{
	ip = function.bytecode.get_start_pointer();
	constants = function.constant_buffer.begin()._Ptr - 128;
}