//
// Created by georg on 09/07/2026.
//

#include "ProductElement.h"


std::pair<std::string, std::string>
splitProduct(const std::string& s)
{
    if (s.size() < 5 || s.front() != '(' || s.back() != ')')
        throw std::runtime_error("Expected product element of the form (a,b)");


    int depth = 0;
    size_t comma = std::string::npos;


    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
            ++depth;
        else if (s[i] == ')')
            --depth;
        else if (s[i] == ',' && depth == 1)
        {
            comma = i;
            break;
        }
    }


    if (comma == std::string::npos)
        throw std::runtime_error("Expected ',' separating product components.");


    auto trim = [](std::string str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last  = str.find_last_not_of(" \t\n\r");


        if (first == std::string::npos)
            return std::string();


        return str.substr(first, last - first + 1);
    };


    std::string left  = trim(s.substr(1, comma - 1));
    std::string right = trim(s.substr(comma + 1,
                                      s.size() - comma - 2));


    return {left, right};
}
