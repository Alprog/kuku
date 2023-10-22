#pragma once

#include <string>
#include "bytecode.h"
#include "localvar_info.h"

namespace rt
{
    class function
    {
    public:
        std::string name;

        bytecode bytecode;
        std::vector<localvar_info> locals;

        void print_locals_info();
    };
}