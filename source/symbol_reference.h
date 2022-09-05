
#pragma once

class token;
class symbol;

class symbol_reference
{
public:
	symbol_reference();

	token* token;
	symbol* symbol;
};