
#pragma once

#include "instruction_type.h"
#include "types.h"
#include "routine.h"
#include "jump_table.h"

#pragma pack(1)
 
struct base_instruction
{
	union
	{
		uint32_t uint_value;
		struct
		{
			uint8_t I;
			uint8_t A;
			uint8_t B;
			uint8_t C;
		};
		struct
		{
			instruction_type op_code;
			uint8_t _;
			uint16_t Bx;
		};
		struct
		{
			int16_t __;
			int16_t sBx;
		};
	};
};

static_assert(sizeof(base_instruction) == 4);