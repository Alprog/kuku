
#pragma once

#include <string>

class Syntax_node
{
public:
	virtual std::u16string get_node_type() { return u"<unknown>"; }
};