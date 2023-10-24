#pragma once

#include <string>
#include "bytecode.h"
#include "localvar_info.h"
#include "instruction_type.h"

namespace rt
{
    class function
    {
    public:
        std::string name;

        bytecode bytecode;
        std::vector<localvar_info> locals;

        const localvar_info& get_local_info(int instruction_offset, int stack_offset) const;

        void print_instructions(bool include_comments);
        void print_locals_info();

        std::string get_comment(byte* ptr, instruction_type type, int offset);
    };
}