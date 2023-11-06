#include "call_frame.h"

call_frame::call_frame(rt::function& function, cell* start)
	: function { &function }
	, stack { stack }
{
	ip = function.bytecode.get_start_pointer();
	constants = function.constant_buffer.end()._Ptr - 128;
}