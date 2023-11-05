#pragma once

#include "opcode.h"
#include "types.h"

#pragma pack(push)
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
			opcode opcode;
			int8_t sA;
			int8_t sB;
			int8_t sC;
		};
		struct
		{
			uint16_t __;
			uint16_t Bx;
		};
		struct
		{
			uint16_t __;
			int16_t sBx;
		};
	};

	int get_argument_value(std::string name) const;
};

#pragma pack(pop)

static_assert(sizeof(base_instruction) == 4);