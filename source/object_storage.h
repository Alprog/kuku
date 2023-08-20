
#pragma once

#include <vector>
#include <stack>
#include "object_header.h"

class object_storage
{
public:
    object_header& get_object(object_index object_index);  
    object_index create_object(class_index class_index);

private:
    void destroy_object(object_index object_index);

    std::vector<object_header> objects;
    std::stack<object_index> holes;
};