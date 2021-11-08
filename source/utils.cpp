
#include "utils.h"

std::vector<std::string> split(std::string line, std::string delimeter)
{
    std::vector<std::string> result;

    size_t start = 0;
    size_t index = line.find(delimeter);
    while (index != std::string::npos)
    {
        if (start != index)
        {
            result.push_back(line.substr(start, index - start));
        }
        start = index + delimeter.size();
        index = line.find(' ', start);
    }
    if (start < line.size())
    {
        result.push_back(line.substr(start));
    }

    return result;
}