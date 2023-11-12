#pragma once

#include "opcode.h"
#include "instruction_mode.h"
#include "inline_operand.h"

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
			uint8_t _;
			uint16_t Bx;
		};
		struct
		{
			uint16_t __;
			int16_t sBx;
		};
		struct
		{
			instruction_mode MB : 1;
			instruction_mode MC : 1;
			uint8_t _ : 5;
			uint8_t breakpoint : 1;
		};
		struct
		{
			instruction_mode M2 : 2;
		};
	};

	int get_argument_value(std::string name) const;

	void set_B_cell(inline_operand operand);
	void set_C_cell(inline_operand operand);
};

#pragma pack(pop)

static_assert(sizeof(base_instruction) == 4);